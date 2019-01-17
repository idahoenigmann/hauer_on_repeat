create table saves (
    inputDate date primary key unique not null,
    input varchar(32) not null,
    delta int not null
);
