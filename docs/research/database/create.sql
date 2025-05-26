CREATE TABLE IF NOT EXISTS sodafactory (
    time    TIMESTAMPTZ  NOT NULL,
    sensorid INTEGER NOT NULL,
    data    DOUBLE PRECISION NOT NULL
);

INSERT INTO sodafactory
    VALUES
        (NOW(), 1, 0.5),
        (NOW(), 2, 0.6),
        (NOW(), 3, 0.7),
        (NOW(), 4, 0.8),
        (NOW(), 5, 0.9),
        (NOW(), 6, 1.0),
        (NOW(), 7, 1.1),
        (NOW(), 8, 1.2),
        (NOW(), 9, 1.3),
        (NOW(), 10, 1.4);