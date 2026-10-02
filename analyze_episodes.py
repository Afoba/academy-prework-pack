# My solution of tasks 3 and 4 (including unit_tests.py)
import csv

usable_values = ['usable', 'unusable']
outcome_values = ['success', 'failure', 'unknown']

def flag_recording(row): # explicit conditions for readability
    usable_check = row['capture_quality'] in usable_values
    outcome_check = row['task_outcome'] in outcome_values
    session_exists = row['session_id'] is not None
    try:
        time_check = float(row['duration_s']) > 0 and int(row['frames']) > 0
    except (ValueError, TypeError):
        time_check = False

    return usable_check and outcome_check and time_check and session_exists or row['capture_quality'] == 'unusable' 

record = {}
flagged_entries = []

try:
    file = open('sample-episodes.csv', 'r')
except FileNotFoundError:
    raise SystemExit("Error: file 'sample-episodes.csv' was not found.")

with open('sample-episodes.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        if not flag_recording(row):
            flagged_entries.append(row)
            continue
        if row['session_id'] not in record.keys():
            record[row['session_id']] = {
                'total': 0,
                'usable': 0,
                'success': 0
            }
        record[row['session_id']]['total'] += 1
        if row['capture_quality'] == 'usable':
            record[row['session_id']]['usable'] += 1
            if row['task_outcome'] == 'success':
                record[row['session_id']]['success'] += 1

total_sessions = sum([record[session]['total'] for session in record])
total_usable = sum([record[session]['usable'] for session in record])
total_success = sum([record[session]['success'] for session in record])

print(f'Total sessions: {total_sessions}')
print(f'Total usable sessions: {total_usable}')
print(f'Total unusable sessions: {total_sessions - total_usable}')
for key, value in record.items():
    print(f'Session {key} usable sessions: {value["usable"]}')
print(f'Total successful sessions: {total_success}')
print(f'Total unsuccessful sessions: {total_usable - total_success}')
print(f'Filtered {len(flagged_entries)} episode(s): {", ".join(row["episode_id"] for row in flagged_entries)}')