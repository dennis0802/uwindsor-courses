INSERT INTO PERSON VALUES(10, 'Jobe Bata', 65, 'nurse');
INSERT INTO PERSON VALUES(20, 'Monica Kap', 80, 'retiree');
INSERT INTO PERSON VALUES(30, 'Peter Good', 22, 'retailer');
INSERT INTO PERSON VALUES(40, 'Kate Lee', 47, 'teacher');
INSERT INTO PERSON VALUES(50, 'Ted Tam', 50, 'doctor');
commit;

INSERT INTO CENTRE VALUES(1, 'DownTn', 'Windsor', 600000, 10);
INSERT INTO CENTRE VALUES(2, 'St Clair', 'Windsor', 400000, 10);
INSERT INTO CENTRE VALUES(3, 'WFCU', 'Windsor', 900000, 50);
INSERT INTO CENTRE VALUES(4, 'Other', 'Windsor', 600000, 50);
commit;

INSERT INTO PCOMPANY VALUES('Astrazeneca', NULL);
INSERT INTO PCOMPANY VALUES('Johnson and Johnson', '1(732)524-0400');
INSERT INTO PCOMPANY VALUES('Moderna', '1(866)663-3762');
INSERT INTO PCOMPANY VALUES('Pfizer', '1(877)633-2001');
INSERT INTO PCOMPANY VALUES('US FDA', '1(888)463-6332');
commit;

INSERT INTO VACCINE VALUES('Astrazeneca', 'Adenoviruses', 'Astrazeneca');
INSERT INTO VACCINE VALUES('Johnson and Johnson', 'Viral vector', 'Johnson and Johnson');
INSERT INTO VACCINE VALUES('Moderna', 'mRNA', 'Moderna');
INSERT INTO VACCINE VALUES('Pfizer', 'mRNA', 'Pfizer');
commit;

INSERT INTO SELLS VALUES('Astrazeneca', 'Astrazeneca', 5.00);
INSERT INTO SELLS VALUES('Johnson and Johnson', 'Johnson and Johnson', 10.00);
INSERT INTO SELLS VALUES('Moderna', 'Moderna', 32.00);
INSERT INTO SELLS VALUES('Pfizer', 'Pfizer', 20.00);
commit;

INSERT INTO VACCINATES VALUES(10, 1);
INSERT INTO VACCINATES VALUES(10, 4);
INSERT INTO VACCINATES VALUES(20, 1);
INSERT INTO VACCINATES VALUES(30, 2);
INSERT INTO VACCINATES VALUES(40, 3);
INSERT INTO VACCINATES VALUES(50, 4);
INSERT INTO VACCINATES VALUES(50, 3);
commit;

INSERT INTO ADMINISTERS VALUES(10, 1, 'Pfizer', '02-apr-21', 1, 13.30);
INSERT INTO ADMINISTERS VALUES(10, 4, 'Pfizer', '12-jun-21', 2, 12.30);
INSERT INTO ADMINISTERS VALUES(20, 1, 'Astrazeneca', '04-mar-21', 1, 9.00);
INSERT INTO ADMINISTERS VALUES(30, 2, 'Moderna', '12-may-21', 1, 11.00);
INSERT INTO ADMINISTERS VALUES(40, 3, 'Pfizer', '20-apr-21', 1, 15.30);
INSERT INTO ADMINISTERS VALUES(50, 4, 'Astrazeneca', '20-apr-21', 1, 10.30);
INSERT INTO ADMINISTERS VALUES(50, 3, 'Pfizer', '23-apr-21', 2, 14.00);
commit;