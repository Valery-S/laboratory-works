CREATE TABLE IF NOT EXISTS unique_number(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    UN INTEGER NOT NULL,
    Name text NOT NULL,
    Surname text NOT NULL,
    Status text NOT NULL ,
    Foto text NOT NULL
);

CREATE TABLE IF NOT EXISTS Enters(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    Entry text NOT NULL,
    UN INTEGER NOT NULL,
    Name text NOT NULL,
    Surname text NOT NULL,
    Status text NOT NULL ,
    Foto text NOT NULL,
    Time text NOT NULL
);

CREATE TABLE IF NOT EXISTS Disturbance(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    Type text NOT NULL,
    number integer not null,
    Time text not null
);

