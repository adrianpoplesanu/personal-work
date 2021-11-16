-- https://www.w3schools.com/php/php_mysql_create_table.asp
CREATE TABLE Users(
id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
firstname VARCHAR(30) NOT NULL,
lastname VARCHAR(30) NOT NULL,
email VARCHAR(50),
password VARCHAR(100),
createddate TIMESTAMP,
modifieddate TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- https://www.w3schools.com/sql/sql_alter.asp
ALTER TABLE Users
ADD role VARCHAR(10);


CREATE TABLE Tasks(
id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
userid INT(6) NOT NULL,
description VARCHAR(50) NOT NULL,
status VARCHAR(50) NOT NULL,
seap_status VARCHAR(50),
createddate TIMESTAMP,
modifieddate TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);