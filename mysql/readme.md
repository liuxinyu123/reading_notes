# 基本命令
启动mysql服务：
1. 打开数据库：  mysql -uroot -p 会车加密码   ,Mac下：mysql -uroot
2. 查看数据库： show databases;        
3. 进入数据库： use XXX;     
4. 表的定义：     
- 创建表：create table xxx;     
- 删除表: drop table xxx;
- 更改表: alter table xxx; 
			字段的更改：
						add column name type;
						drop column name;
						change column oldname newname type;   
	查看表结构：desc xxx;
5. 表的操作：     
- 插入：insert into xxx values(....);       
- 查看：select * from xxx ;   后面可以加where      
- 删除：delete from xxx where ...;      
- 修改：update xxx set ... where ...;
6. 其它：
> show create database xxx;//查看状态    
> show create table xxx;//      
> status;//查看服务器状态

# 字段类型     
1. 数值    
>  int(n)   最大11位  unsigned 为10位,当指定位数时，不足做零填充，默认不填充，需要zerofill       
>  float         
2. 字符串      
>  char(n)    比varchar快    空间不可变， 检索速度快  n最大255字节
>  varchar(n)     比char节约空间  空间根据实际而定(实际+1)，最大为n,最大为65535字节  
>  text    65535字节  存储(l + 2) 
>  longtext   42亿字节      存储(l + 4)  
3. 日期        
>  date       空间占用 3 字节
>  time       空间占用 3 字节
>  datetime   空间占用 8 字节    
>  timestamp  空间占用 4 字节    
>  year       空间占用 4 字节     

# 字段属性    
>  unsigned    无符号    
>  zerofill     零填充  int(3) 不够3位前面补零  
>  auto_increment   自增 
>  null           默认属性  ，允许位null
>  not null        不允许为null
>  default       与not null 配合使用   ，使用默认值   



