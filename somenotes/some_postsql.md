#### postgre
(http://www.cnblogs.com/weaming/p/postgre-basic.html )
    一. 安装
      1. linux
        postgresql-client 、 postgresql (server) 、 pgadmin3 (GUI)


    1. 登录（gaussdb, gsql)
      *sql -h host -d db -U user -W password
      \l  查看系统中现存数据库
      \c db 切换到另外的数据库
      \dt 查看表
      \d table 查看表结构
      \du [db name] 列出用户角色
      \! shell里执行命令
      \di 查看索引
      \q 退出
      (某host加权限 pg_ha.conf)
    2. 创建
      创建用户数据库
      create database user_db owner user;
      （当前数据库）用户
      create user dbuser with password "xxx";
      create role xxx in xxx_group;???? to be checked
      创建schema（集合）
      create schema user_db authorization user;
    3. 恢复数据库
      *sql dbname < db.sql
      *sql -h host -d db -f backup.sql
    4. 常用命令
      创建表
      create table user_tb(name type, date type);
      插入数据
      insert into user_tb(name, date) values('11', '2018');
      查询
      select * from user_tb where blabla;
      修改用户密码
      \password # or
      alter user user_name with password "pass";
      更新数据
      update user_tb set name='22' where name='11';
      删除数据
      delete from user_tb where name='22';
      删除表
      drop table if exists user_tb;
      删除用户
      drop user user_name;
      删除数据库
      drop database db_name;
    5. 备份
      pg_dump db_name > /path/db.bak
      # 单个db
      pg_dump -h host -d db -f bk.sql
      # 所有
      pg_dumpall > /path/db.baki
    6. 还原
      create target_db
      *sql target_db_name < /path/db.bak
      *sql newdb< /path/createobjects.sql
      # 单个db
      *sql -h host -d db -f bak.sql
