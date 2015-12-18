#!/usr/bin/env python
import csv
import re

class NoReadingException(Exception):
    pass

def averageHourlyReading(fn, hour, column):
    """This function analyzes CSV files as used by Environment Canada for
    monthly reporting historic weather data. Each row of the file named
    fn is assumed to contain readings for a specific year (integer in
    column 2), month (integer in column 3), day (integer in column 3)
    and time (24 hours in format 'hh:00'). Numerical readings are
    temperature (column 7), dew point (column 9), relative humidity
    (column 11), wind direction (column 13), wind speed (column 15), and
    pressure (column19). Each value in the file is in double quotes and
    the values on one row are separated by comma. It is assumed that a
    comma does not appear within double-quoted values. The function
    calculates the average value of the specified column at the
    specified hour, for all entries in the file. There must be a header
    present, a row with "Date/Time" in the first column. All rows after
    the header until the end of the file are taken into account. The
    preamble, all rows before the header, is ignored. No assumption is
    made about the order of the rows. Rows may be incomplete, i.e. have
    only some of the above columns with readings. Columns that are not
    mentioned above are ignored.
    It is assumed that if a reading is present, it is in numeric format.
    It is also assumed that the file is present and can be read. The
    function raises NoReadingException if there are less than 15 valid
    readings for the specified hour in the specified column"""
    lines = []
    column = column - 1
    total, ctr, avg = 0.0, 0, 0
    f = open(fn, 'r', encoding="utf­8")
    csvReader = csv.reader( f, delimiter="," )
    for i in csvReader:
        lines.append(i)
    for y in range(17,len(lines)):
        if len(lines[y]) > column and int(lines[y][4][:-3]) == hour and lines[y][column] != "":
            if re.search(r'[\d]+[.]?', lines[y][column]):
                total += float(lines[y][column])
                ctr += 1
                avg = total / ctr
    if ctr < 15: raise NoReadingException
    return avg


averageHourlyReading('eng-hourly-05012014-05312014.csv', 0, 7) # temperature: 10.97...
averageHourlyReading('test2.csv', 3, 7) # temperature: 6
averageHourlyReading('test2.csv', 3, 9) # dew point: 6.07...
averageHourlyReading('test2.csv', 3, 11) # humidity: 84.73...


def averageHourlyReadingPlus(fn, hour, column): 
    """This function analyzes CSV files as used by Environment Canada
    for monthly reporting historic weather data. Each row of the file
    named fn is assumed to contain readings for a specific year (integer
    in column 2), month (integer in column 3), day (integer in column 3)
    and time (24 hours in format 'hh:00'). Numerical readings are
    temperature (column 7), dew point (column 9), relative humidity
    (column 11), wind direction (column 13), wind speed (column 15), and
    pressure (column19). Each value in the file is in double quotes and
    the values on one row are separated by comma. It is assumed that a
    comma does not appear within double-quoted values. The function
    calculates the average value of the specified column at the
    specified hour, for all entries in the file. There must be a header
    present, a row with "Date/Time" in the first column. All rows after
    the header until the end of the file are taken into account. The
    preamble, all rows before the header, is ignored. No assumption is
    made about the order of the rows. Rows may be incomplete, i.e. have
    only some of the above columns with readings. Columns that are not
    mentioned above are ignored.
    A reading in a non-numerical format is simply ignored. The function
    raises NoReadingException if there is an error in opening or reading
    the file or if there are less than 15 valid readings for the
    specified hour in the specified column in the file"""
    lines = []
    column = column - 1
    total, ctr, avg = 0.0, 0, 0
    f = open(fn, 'r', encoding="utf­8")
    csvReader = csv.reader( f, delimiter="," )
    for i in csvReader:
        lines.append(i)
    for y in range(17,len(lines)):
        if len(lines[y]) > column and int(lines[y][4][:-3]) == hour and lines[y][column] != "":
            if re.search(r'[\d]+[.]?', lines[y][column]):
                total += float(lines[y][column])
                ctr += 1
                avg = total / ctr
    if ctr < 15: raise NoReadingException
    return avg


def testReadingPlus(fn, hour, column):
    print('average of', column, 'at', hour, end = ': ')
    try:
        print(averageHourlyReadingPlus(fn, hour, column))
    except NoReadingException:
        print('cannot be determined')
    except FileNotFoundError:
        print('FileNotFoundError, no such file')
        
testReadingPlus('eng-hourly-06012015-06302015.csv', 0, 7) # temperature: NoReadingException, not enough readings
testReadingPlus('eng-hourly-05012014-05312014.csv', 0, 7) # temperature: 10.97...
testReadingPlus('test1.csv', 0, 7) # temperature: NoReadingException, no readings at all
testReadingPlus('test2.csv', 3, 7) # temperature: 6
testReadingPlus('test2.csv', 3, 9) # dew point: 6.07...
testReadingPlus('test2.csv', 3, 11) # humidity: 84.73...
testReadingPlus('test2.csv', 3, 13) # wind: NoReadingException, not enough readings
testReadingPlus('test3.csv', 3, 13) # wind: FileNotFoundError, no such file
