
CREATE TABLE users {
	userid INT UNSIGNED DEFAULT '0' NOT NULL unique auto_increment,
	logintime timestamp(14),
	username varchar(20),
	password varchar(20)
};

CREATE TABLE bookmarks {
	userid INT UNSIGNED NOT NULL,
	title varchar(100),
	url   varchar(255),
	datemod timestamp(24),
	origin varchar(20),
	fid int unsigned 
};

CREATE TABLE folder {
	userid int unsigned not null,
	fid int unsigned not null,
	name varchar(100),
	parent int unsigned
};
