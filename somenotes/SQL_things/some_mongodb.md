#### MongoDB
    一. 安装与启动
      -- # http://www.runoob.com
      -- # https://docs.mongodb.com/getting-started/python/client/
      -- # https://api.mongodb.com/python/current/tutorial.html
      1. windows
      -- # to start mongodb service if mongo.conf exists
      -- # 加双引号，或者不加引号
      -- # mongod.exe --config "c:\mongodb3.4\mongo.conf"
      -- # not config , creat data/db in c:\
      -- # mongod.exe --dbpath c:\data\db
      -- # Linux , packages are *linux*.tgz
      -- # start : ./bin/mongod --config {pwd}/mongo.conf
      -- # GUI robomongo (opensource), CTR+ENTER exec query
      2. Arch
      pacman -S mongodb (mongodb-tools)
      -- # before start mongodb, use the default path
      -- # creat new dir in / (or define other path)
      sudo mkdir -p /data/db
      -- # start mongodb.service
      sudo systemctl start mongodb(not mongod)
      -- # wait mongodb start
      -- # get into mongo shell
      mongo
    二. 常用命令
      -- ## Command: insert(save), find, findOne, drop,update(save)
      -- ## sort, skip, limit, ensureIndex(索引), aggregate(聚合)
      -- ## remove
      -- ## default collection IS runoob
      -- # creat a collection, if capped true, size is needed ,not changable
       db.createCollection('name', {capped:true, size:1000000})
      -- # use default collection (table)
       db.runoob.insert({name:value}) --insert
       db.runoob.find()  --find
       1. 查看
      -- # show all dbs(new db need to put into data)
       show dbs
      -- # show current db
       db
      -- #creat db
      -- #if not exists, creat; else switch to the db
       use Database_name
      -- # delete current db,
       db.dropDatabase()
      -- # show collections(tables)
       show tables
      -- # delete collection, assume now table is mdb
       db.mdb.drop()
      -- # update param
      -- save()
       db.runoob.update(
      	{key:value}, --<query which need to update>
      	{$set:{key:value}},--#<update which to update to>
      	-- NOT NECESSARY
      	{
      		-- boolean: TRUE， if update not exists ,insert
      		upsert: FALSE --(default false, not exists , not insert)
      		-- boolean: TRUE, update all matchs
      		multi: FALSE --default false, update the first find
      		writeConcern: <document> --exception
      	}
       )
      -- # delete document in collection
       db.mdbc.remove( --version 2.6+
      	{key:value}, -- <query>
      	{
      		justOne: <boolean> -- True or 1, onlye delete one doc
      		writeConcern: <document> -- exception
      	}
       )
      -- # query document, can pass into multi params
      -- 优先级
      -- ### level to run: sort > skip > limit (no matter where it is)
       db.runoob.find(
      	query, -- not necessary, query condition
      	projection -- not nec.., return query value, which to show
      	)
      -- Selection ##
      -- query all data, select and diplay key, not _id
      -- 1 true show, 0 false hide, _id is defualt set to display
      -- apply _id:0 to hide. if got one key is 1 or true,
      -- display true data ; if key is 0, dispaly the rest data.
      -- db.runoob.find({},{key:1,_id:0})
       db.runoob.findOne() -- only return one ducument
       --pretty()
      -- # format output (for humanbeings)
       db.runoob.find().pretty()
       --limit()
      -- # limit number of doc to show, if no num given, show all
      -- # start from current data's start and to it's num=index
       db.runoob.find({},{key:1}).limit(number)
      --skip()
      -- # skip number of data from first to number, show rest of it
       db.runoob.find({},{key:1}).skip(number)
      -- # skip and limit to set data in different page
      -- # hide the fisrt 2 doc, show 100 of the rest
       db.runoob.find({},{key:1}).skip(2).limit(100)
      --sort()
      -- sort data with given a key,key:1 from low to high升序;
      -- key:-1 from high to low降序
      db.runoob.find().sort({key:1})/db.runoob.find().sort({key:-1})

      --################# creat index
      db.runoob.ensureIndex(...) -- wait for detail
      --################# sum avg min max .... and more
      db.runoob.aggregate(...) -- wait for detail
      -- Conditions
      $gt > 	 	$lt <
      $gte >=		$lte <=
      -- ##  Conpare NoSQL mongo with RDBMS SQL
      equal		{key:value}			| 	where key=value
      lessthan	{key:{$lt:value}}	|	where key<value
      lt/equal	{key:{$lte:value}}	|	where key<=value
      greaterthan	{key:{$gt:value}}	|	where key>value
      gt/equal 	{key:{$gte:value}}	|	where key>=value
      notequal	{key:{$ne:value}}	|	where key!=value

      -- ##  Boolean condition
      -- AND
      db.runoob.find({key1:value1, key2:value2}).pretty()
      # where key1=value1 AND key2=value2
      -- OR
      db.runoob.find(
      	{
      		$or:[
      			{key1:value1}, {key2:value2}
      		]
      	}
      ).pretty()
      # where key1=value1 OR key2=value2
      -- AND & OR
      db.runoob.find({key:{$gt:value},$or:[{k1:v1},{k2:v2}]}).pretty()
      # where key>value AND (k1=v1 OR k2=v2)
      db.runoob.find({key:{$gt:100}})
      # Select * from runoob where key > 100
      db.runoob.find({key:{$gt:100, $lt:200}})
      # Select * from runoob where key>100 AND key<200
