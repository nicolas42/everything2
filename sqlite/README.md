This is an example of how to use sqlite, which apparently is the most used database engine in the world.


Getting started 
-------------------

1. Run make 
2. run the sql interpreter (a.out)
3. copy/paste sample.sql into the terminal or .open sample.db

    make 
    ./a.out 
    .open sample.db 

4. look at sample.png
5. Try some queries (examples below)



Demo queries for sample.db
----------------------------------------------------------


-- limit should usually be at the end 
-- search with like
-- underscore means any single character, % means any number of characters
-- Inner join combines records from two tables whenever there are matching values in a field common to both tables.


select cust_name, cust_city from customer;

select * from customer limit 5;

select distinct agent_code from customer order by agent_code;

select * from customer where agent_code = 'A003';

select * from customer where agent_code like '%A00%' limit 5;
SELECT * FROM departments WHERE dept_name LIKE 'A____';


SELECT COUNT(distinct agent_code) FROM customer;


SELECT agents.agent_name, customer.cust_name
FROM customer INNER JOIN agents 
ON agents.WORKING_AREA = customer.WORKING_AREA 
order by agents.agent_code limit 10;



-- List databases, tables 

.databases
.tables


source https://learnxinyminutes.com/docs/sql/