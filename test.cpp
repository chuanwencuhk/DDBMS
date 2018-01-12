/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
 */
step 1. DROP TABLES;
drop table sal;
drop table emp;
drop table job;
drop table asg;

step 2. CREATE 4 TABLES.

create table sal(title char(100),sal integer);
create table emp(eno char(100),ename char(100), title char(100));
create table job(jno char(100),jname char(20), budget integer, loc char(20));
create table asg(eno char(100), jno char(20), resp char(20), dur integer);


create table publisher(id integer,name char(100),nation char(3));
create table book(id integer,title char(100),authors char(20),publisher_id integer,copies integer);
create table customer(id integer,name char(25),rank integer);
create table orders (customer_id integer,book_id integer,quantity integer);

frag -hor publisher id < 104000 and nation = 'PRC' db1 * id < 104000 and nation = 'USA' db2 * id >= 104000 and nation = 'PRC' db3 * id >= 104000 and nation = 'USA' db4;

frag -hor book id < 205000 db1 * id >= 205000 and id < 210000 db2 * id >= 210000 db3;

frag -ver customer (id,name) db1 * (id,rank) db2;

frag -hor orders customer_id < 307000 and book_id < 215000 db1 * customer_id < 307000 and book_id >= 215000 db2 * customer_id >= 307000 and book_id < 215000 db3 * customer_id >= 307000 and book_id >= 215000 db4;

frag -hor asg eno < 'E1000' and jno < 'J0500' db1 * eno < 'E1000' and jno >= 'J0500' db2 * eno >= 'E1000' and jno < 'J0500' db3 * eno >= 'E1000' and jno >= 'J0500' db4;



use foo;
show tables;
show columns from emp;
show columns from asg;
show columns from job;
show columns from sal;

step 3. MAKE FRAGMENTS.

cd /home/wcw/ddb_parser/rpc_sql
rm tmp

load 'sal.csv' into local table sal ;

frag -none sal db1;


frag -ver emp (eno,ename)	db1 * (eno,title) db2;

create table emp(eno char(100),ename char(100), title char(100));

frag -hor emp eno < 'E1000' and title < 'N' db1 * eno < 'E1000' and title >= 'N' db2 * eno >= 'E1000' and title < 'N' db3 * eno >= 'E1000' and title >= 'N' db4;



frag -hor job jno < 'J0500' db1 * jno >= 'J0500' db2;

frag -mix job jno < 'J0500' (jno,jname,budget) db1 * jno < 'j0500' (jno,loc) db2 * jno >= 'j0500' (jno,jname,budget) db3 * jno >= 'J0500' (jno,loc) db4;






select * from emp where emp.eno > 'E0997' and emp.eno < 'E0999';
select * from emp,asg where emp.eno = asg.eno;
select * from emp,sal where emp.title=sal.title;
select * from emp,sal where emp.title=sal.title and emp.title = 'IT Director';

select emp.eno,job.jno,emp.title,job.loc from emp,job,sal,asg where emp.title=sal.title and emp.eno=asg.eno and job.jno=asg.jno and job.jno<='J0400' and emp.title = 'IT Director';




cd /var/lib/mysql-files

select * from emp;select * from asg;
select * from asg;
select * from job;
select * from sal;

step 3. SIMPLE SELECT.

select * from emp where emp.eno >= 'E0990' AND emp.eno < 'E1001';

select jno from job where jname = 'Project #999';

step 4. DELETE

delete from emp;

step 5. UPDATE
update job set jname = 'Project #988' where jno = 'J0999';

insert into emp values ('E2500','wangchuanwen','teacher');
select * from emp where eno = 'E2500';

select * from emp where eno = 'E2497';

select * from job  where jno = 'J0999';
select * from asg where eno = 'E1159';


insert into job values ('J1230','Project #2000','20000','Newyork City');

select * from job where jno='J1230';

