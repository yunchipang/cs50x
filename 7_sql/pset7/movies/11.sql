SELECT movies.title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
JOIN stars ON stars.movie_id = movies.id
WHERE stars.person_id = (SELECT id from people WHERE name = "Chadwick Boseman")
ORDER BY ratings.rating DESC
LIMIT 5;