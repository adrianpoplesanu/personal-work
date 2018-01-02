--CREATE TABLE user_roles (
--  user_role_id int(11) NOT NULL AUTO_INCREMENT,
--  username varchar(45) NOT NULL,
--  role varchar(45) NOT NULL,
--  PRIMARY KEY (user_role_id),
--  UNIQUE KEY uni_username_role (role,username),
--  KEY fk_username_idx (username),
--  CONSTRAINT fk_username FOREIGN KEY (username) REFERENCES users (username));

CREATE TABLE UserData (
    id int(11) NOT NULL,
    name varchar(45) NOT NULL,
    address varchar(200),
    jnumber varchar(45),
    tip int(1) NOT NULL,
    autorizatie_mediu varchar(45),
    UNIQUE KEY uni_user_data_id (id),
    KEY fk_user_data_id_idx(id),
    CONSTRAINT fk_user_data_id FOREIGN KEY (id) REFERENCES users(id)
);

INSERT INTO UserData(id,name,address,jnumber,tip,autorizatie_mediu)
VALUES (1,'S.C. Urban Group S.R.L.', 'Str. Compozitorilor Nr. 55, sector 7, Bucuresti', 'J40/12345/2016', 1, '14/12.02.2006');

insert into UserData values(2, 'American Greetings Corp', '1st American Road, Clevland, Ohio', 'J40/12345/1890', 2, 'NO');

ALTER TABLE UserData ADD cui varchar(45);
ALTER TABLE UserData ADD description varchar(200);

ALTER TABLE UserData ADD persoana_contact varchar(100);
ALTER TABLE UserData ADD email varchar(100);
ALTER TABLE UserData ADD telefon varchar(20);
ALTER TABLE UserData ADD oras varchar(45);
ALTER TABLE UserData ADD judet varchar(45);
ALTER TABLE UserData ADD cod_postal varchar(10);
ALTER TABLE UserData ADD website varchar(45);

update UserData set cui='33993810' where id=1;
update UserData set persoana_contact='Marius Dobre', email='mdobre@yahoo.com', telefon='0746225588', oras='Bucuresti', cod_postal='0123670' where id=1;

