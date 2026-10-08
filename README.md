# Summary of the work done

## Tasks 1-4

The script `analyze_episodes.py` is responsible for performing an analysis on a given CSV file containing episode data. This analysis counts the number of sessions, reports on their overall usability overall and per session, and counts the number of successful sessions among the usable entries. Additionally, it filters out any 'usable' entries with suspicious data, such as missing values, or having its duration be <= 0. 

To run it, use the following command in the terminal:
```sh
python3 analyze_episodes.py [file_name]
```

Many input errors were covered in the script. Passing a non-existant file or a file of a different extension will output a message without displaying Python's native error messages to the user. 

Additionally, the script `unit_tests.py` presents various unit tests to the `flag_recording` function of `analyze_episodes.py`. The following cases are tested:

* A usable and successful entry;
* A usable and failed entry;
* A unusable entry;
* A usable entry with invalid frames;
* A usable entry with invalid duration;
* A usable entry with null values.

To run it, use the following command in the terminal:

```sh
python3 unit_tests.py
```
----------------

## Tasks 5-8