# Python test script to test the TimescaleDB database connection and basic operations at 22000 write operations per second and quits when ctrl+c is pressed.
# This script assumes that you have a PostgreSQL/TimescaleDB database running and a table named 'sodafactory' created with the following schema:
# CREATE TABLE IF NOT EXISTS sodafactory (
#     time    TIMESTAMPTZ  NOT NULL,
#     sensorid INTEGER NOT NULL,
#     data    DOUBLE PRECISION NOT NULL
# );

import psycopg2
import time
import sys
import signal
import os



# Connect to the PostgreSQL database
conn = psycopg2.connect(
    host="localhost",
    database="postgres",
    user="postgres",
    password="123"
)
writes = 0
def quit(signal_number,frame):
    conn.close()
    print("Writes: " + str(writes))


signal.signal(signal.SIGINT, quit)



while True:
    # Create a cursor object
    cur = conn.cursor()
    queryStr = "INSERT INTO sodafactory (time, sensorid, data) VALUES "
    for i in range(0,99):
        queryStr += "  (NOW(), 1, 13.2),"

    queryStr += " (NOW(), 1, 13.2);"
    # Execute a query to insert data into the table using NOW() for the time column
    cur.execute(queryStr)

    # Commit the transaction
    conn.commit()
    writes += 1
    # Close the cursor
    cur.close()
    # Sleep for a short time to control the rate of insertion
    time.sleep(0.000078)  # 1/22000, 22000 writes per second
    

