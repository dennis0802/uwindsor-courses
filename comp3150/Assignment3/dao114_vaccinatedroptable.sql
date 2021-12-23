delete from ADMINISTERS;
delete from VACCINATES;
delete from SELLS;
delete from VACCINE;
delete from PCOMPANY;
delete from CENTRE;
delete from PERSON;
commit;

drop table ADMINISTERS cascade constraints;
drop table VACCINATES cascade constraints;
drop table SELLS cascade constraints;
drop table VACCINE cascade constraints;
drop table PCOMPANY cascade constraints;
drop table CENTRE cascade constraints;
drop table PERSON cascade constraints;
commit;
