# Unit tests for the analyze_episodes.py module,
# meant as continuation of the task 4.
import unittest
from analyze_episodes import flag_recording

class TestFlagRecording(unittest.TestCase):
    def test_flag_recording_usable_success(self):
        row = {
            'session_id': 'A',
            'capture_quality': 'usable',
            'task_outcome': 'success',
            'duration_s': '10.0',
            'frames': '100'
        }
        self.assertTrue(flag_recording(row))

    def test_flag_recording_usable_failure(self):
        row = {
            'session_id': 'A',
            'capture_quality': 'usable',
            'task_outcome': 'failure',
            'duration_s': '5.0',
            'frames': '50'
        }
        self.assertTrue(flag_recording(row))

    def test_flag_recording_unusable(self):
        row = {
            'session_id': 'A',
            'capture_quality': 'unusable',
            'task_outcome': 'unknown',
            'duration_s': '1.0',
            'frames': '10'
        }
        self.assertTrue(flag_recording(row))

    def test_flag_recording_invalid_duration(self):
        row = {
            'session_id': 'A',
            'capture_quality': 'usable',
            'task_outcome': 'success',
            'duration_s': '-1.0',
            'frames': '100'
        }
        self.assertFalse(flag_recording(row))

    def test_flag_recording_invalid_frames(self):
        row = {
            'session_id': 'A',
            'capture_quality': 'usable',
            'task_outcome': 'success',
            'duration_s': '10.0',
            'frames': '-10'
        }
        self.assertFalse(flag_recording(row))

    def test_flag_null_values(self):
        row = {
            'session_id': None,
            'capture_quality': 'usable',
            'task_outcome': None,
            'duration_s': None,
            'frames': None
        }
        self.assertFalse(flag_recording(row))

if __name__ == '__main__':
    unittest.main()