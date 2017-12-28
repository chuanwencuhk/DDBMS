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

CHECK ON ALL SITES.

use foo;
show tables;
show columns from emp;
show columns from asg;
show columns from job;
show columns from sal;

step 3. MAKE FRAGMENTS.

cd /home/wcw/ddb_parser/rpc_sql
rm tmp

load 'sal.csv' into sal ;

frag -hor emp eno < 'E1000' and title < 'N' db1 * eno < 'E1000' and title >= 'N' db2 * eno >= 'E1000' and title < 'N' db3 * eno >= 'E1000' and title >= 'N' db4;

frag -hor asg eno < 'E1000' and jno < 'J0500' db1 * eno < 'E1000' and jno >= 'J0500' db2 * eno >= 'E1000' and jno < 'J0500' db3 * eno >= 'E1000' and jno >= 'J0500' db4;

frag -hor job jno < 'J0500' db1 * jno >= 'J0500' db2;



cd /var/lib/mysql-files

select * from emp;select * from asg;
select * from asg;
select * from job;
select * from sal;

step 3. SIMPLE SELECT.

select * from emp where emp.eno >= 'E0990' AND emp.eno < 'E1001';

select jno from job where jname = 'Project #999';

update job set jname = 'Project #988' where jno = 'J0999';

step 4. DELETE

delete from emp;