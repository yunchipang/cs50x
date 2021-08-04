-- Keep a log of any SQL queries you execute as you solve the mystery.

-- find crime -> happened at 10:15am
SELECT * FROM crime_scene_reports
WHERE street = "Chamberlin Street" AND month = 7 AND day = 28;

-- 3 interviews on the same day which mentions the thief
SELECT * FROM interviews WHERE month = 7 AND day = 28
AND transcript LIKE "%thief%";

-- 1. Ruth
-- person who leaves the courthouse between 10:15-10:25
SELECT license_plate FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25
AND activity = "exit";
-- list of license plates of the suspect

-- 2. Eugene
-- person withdrawed money at ATM on Fifer street
SELECT person_id FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw");
-- list of suspect's person_id

-- 3. Raymond
SELECT caller, receiver FROM phone_calls
WHERE month = 7 AND day = 28 AND duration < 60;
-- list of suspected numbers of callers and receivers

-- destination of the 1st flight out of fiftyville on 7/29: id=4, city=London
SELECT city from airports WHERE id IN
(SELECT destination_airport_id FROM flights
WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

-- find thief
SELECT name FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit")
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
AND phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1));

-- find accomplice
SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls 
WHERE month = 7 AND day = 28 AND duration < 60
AND caller = (SELECT phone_number FROM people WHERE name = "Ernest"));