## select 数据库中提取数据
- select 字段 from 表


- select distinct 字段 from 表
> 选取该字段不同的值

- select 字段 from 表 where 条件
> 选取满足条件的记录

    and 且
    or 或
    not 非
    between A and B 数值介于A和B之间
    not between A and B 数值不介于A和B之间
    in 指定多个可能值 
    is null 空值判断
    like 模糊搜索
> %表示多个字符 _表示单个字符

- select 字段 from 表 order by 字段 [asc升序|desc降序];     
## update 更新数据库中数据
update 表 set 字段 = 值 where 条件
## delete 删除数据库中数据
delete from 表 where 条件 
> drop、truncate、 delete 

> drop是直接删除整个表，一干二净

> truncate是删除表中记录，但保留表结构，数据不可恢复

> delete from也是删除 表中记录，保留表结构，但数据可恢复

## insert into 向数据库中插入新数据
insert into 表 (字段) values (值)

## limit 
当 LIMIT 后面跟两个参数的时候，第一个数表示要跳过的数量，后一位表示要取的数量

    select* from article LIMIT 1,3 

> 就是跳过 1 条数据，从第 2 条数据开始取，取 3 条数据，也就是取 2、3、4 三条数据

当 LIMIT 后面跟一个参数的时候，该参数表示要取的数据的数量

    select * from 表 limit 3 

> 选取前三条数据

配合offset使用

    select * from 表 limit 3 offset 1

和第一条效果一样

## top
select top 数字|百分比 字段名 from 表 

    //选取表中前百分之50
    SELECT TOP 50 PERCENT * FROM Websites;
    
配合 order by 可以选取后n行

    select top 数字|百分比 字段名 from 表名 order by id desc

mysql中可以使用limit实现

## join 连接

    select 字段 from 表1 join 表2 on 条件

- INNER JOIN：如果表中有至少一个匹配，则返回行
- LEFT JOIN：即使右表中没有匹配，也从左表返回所有的行
- RIGHT JOIN：即使左表中没有匹配，也从右表返回所有的行
- FULL JOIN：只要其中一个表中存在匹配，则返回行

on 和 where 的区别，前者不管条件是否为真都会返回左表中的记录，后者条件不会真就全部过滤掉

## union 连接两个select的结果

    select 字段 from 表 union select 字段 from 表


- union 只会列出不同值
- union all可以列出所有值

SELECT INTO 语句从一个表复制数据，然后把数据插入到另一个新表中

    INSERT INTO table2
    (column_name(s))
    SELECT column_name(s)
    FROM table1;

 select into from 要求目标表不存在，因为在插入时会自动创建；insert into select from 要求目标表存在

## create database 创建数据库
create database 库名

## create table 创建表
    create table 表名
    (
    字段名1 数据类型(大小)  约束,
    column_name2 data_type(size) constraint_name,
    column_name3 data_type(size) constraint_name,
    ....
    );

constraint_name

- NOT NULL - 指示某列不能存储 NULL 值。

- unique - 保证某列的每行必须有唯一的值。

主码

- primary key - NOT NULL 和 UNIQUE 的结合。确保某列（或两个列多个列的结合）有唯一标识，有助于更容易更快速地找到表中的一个特定的记录。

外键

- foreign key - 保证一个表中的数据匹配另一个表中的值的参照完整性。
- check - 保证列中的值符合指定的条件。
- default - 规定没有给列赋值时的默认值。
 
## create index 创建索引

    create index 索引名
    on 表 (字段)

## drop 删除

    drop index table_name.index_name 删除索引
    drop table table_name 删除表
    drop database database_name 删除数据库
    truncate table table_name 只删除表中内容

database数据库 -> table表 ->字段|索引index

## alter table修改表
    
    alter table table_name add 字段名 datatype 约束
    alter table table_name drop column 字段名
    alter table table_name alter column 字段名 datatype


