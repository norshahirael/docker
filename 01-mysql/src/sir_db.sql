USE sir_db;

CREATE TABLE mytable (
  `user` VARCHAR(255), 
  `points` INT, 
  `datetime_stamp` DATETIME, 
  PRIMARY KEY (`points`)
);

INSERT INTO mytable (`user`, `points`, `datetime_stamp`) VALUES
('jeonghan', 135, '2023-04-07 13:09:00'), 
('deokyeom', 789, '2023-02-22 17:55:00'), 
('scoups', 456, '2023-04-29 11:30:00');
