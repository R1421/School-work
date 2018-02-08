# List all the state names and their two letter codes
select name,statecode from states;


# Write a query to report the information for all counties whose names start with "Prince"
select * from counties where name like "Prince%" order by statecode;


# Write a single query to list only the population in year 2010 for the state represented by Sen. Richard Luger. Output column populate_2010
select t.population_2010 from states t INNER JOIN senators s ON t.statecode=s.statecode where s.name="Richard Lugar";


# Write a single query to report only the total number of the counties in "Maryland". The query should not hard-code the state code for Maryland (join the two tables in the where clause)
select count(*) from counties inner join states on states.statecode=counties.statecode where states.name="Maryland";


# Write a single query to find the name of the state that was admitted last into the union. Hint: Use a nested subquery
select name from states where admitted_to_union = (select max(admitted_to_union) from states);


# Find all democratic (i.e. with affiliation D) senators that are not charman of any committee or sub-committee. Output columns name Order by name
select * from senators left join committees on senators.name=committees.chairman where committees.chairman is NULL and senators.affiliation = 'D';
