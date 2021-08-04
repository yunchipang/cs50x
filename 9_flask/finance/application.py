import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    data = db.execute("SELECT symbol, sum(shares) FROM transactions WHERE user_id = ? GROUP BY symbol", session['user_id'])
    # get current cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']

    table = []
    total = 0
    for i in data:
        d = {}
        result = lookup(i['symbol'])
        d['symbol'] = i['symbol']
        d['name'] = result['name']
        d['shares'] = i['sum(shares)']
        d['price'] = result['price']
        d['total'] = float(result['price'])*i['sum(shares)']
        total += d['total']
        table.append(d)
    return render_template("index.html", table=table, total=total, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        result = lookup(symbol)

        # input error checking
        try:
            shares = int(shares)
        except:
            return apology("please enter a positive integer", 400)

        if shares < 0:
            return apology("please enter a positive number", 400)
        elif not symbol:
            return apology("must have symbol", 400)
        elif not result:
            return apology("invalid symbol", 400)

        # get current cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']

        if float(result['price']) * int(shares) > float(cash):
            return apology("transaction failed, cash not enough", 400)

        # update transactions
        db.execute("INSERT INTO transactions (user_id, shares, price, datetime, symbol) VALUES (?, ?, ?, ?, ?)",
                    session['user_id'], shares, result['price'], datetime.now(), symbol)
        # update users
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                    float(cash) - float(result['price']) * int(shares), session['user_id'])

        return redirect('/')

    else: # request.method == "GET"
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    table = db.execute("SELECT symbol, shares, price, datetime FROM transactions WHERE user_id = ?", session['user_id'])
    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", quote=quote)
    else: # request.method == "GET"
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # qurey all existing usernames in the database
        all_username = db.execute("SELECT username FROM users")
        usernames = []
        for user in all_username:
            usernames.append(user['username'])
        print(usernames)

        # check username input
        if not username:
            return apology("must provide username", 400)
        # check password input
        elif not password:
            return apology("must have password", 400)
        # check comfirmation input
        elif not confirmation:
            return apology("must have password confirmation", 400)
        # check if username already exists
        elif username in usernames:
            return apology("username already exists, please try again", 400)
        # check if password and confirmation matches
        elif password != confirmation:
            return apology("password did not match", 400)

        # insert user registration into database
        password_hashed = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hashed)

        # redirect the user to homepage
        return redirect("/")

    # request.method == "GET"
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # symbols available for sell
    data = db.execute("SELECT symbol, sum(shares) FROM transactions WHERE user_id = ? GROUP BY symbol", session['user_id'])

    symbols = []
    for s in data:
        symbols.append(s['symbol'])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        result = lookup(symbol)
        cost = float(result['price']) * int(shares)

        for d in data:
            if d['symbol'] == symbol:
                current_share = d['sum(shares)']

        # shares < 0
        if int(shares) < 0:
            return apology("please enter a positive number", 400)
        # shares not enough
        elif int(shares) > int(current_share):
            return apology("your stocks are not enough", 400)

        # update transactions
        db.execute("INSERT INTO transactions (user_id, shares, price, datetime, symbol) VALUES (?, ?, ?, ?, ?)",
                    session['user_id'], -int(shares), result['price'], datetime.now(), symbol)
        # update users
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']
        db.execute("UPDATE users SET cash = ? WHERE id = ?", float(cash) + float(result['price']) * int(shares), session['user_id'])
        return redirect('/')

    else: # request.method == "GET"
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
