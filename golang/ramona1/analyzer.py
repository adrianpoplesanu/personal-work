import sys
import face_recognition
import json

def format_points(points):
    formatted_points = []
    for point in points:
        formatted_points.append({'x': point[0], 'y': point[1]})
    return formatted_points

if __name__ == '__main__':
    filename = sys.argv[1]
    image = face_recognition.load_image_file(filename)
    face_landmarks_list = face_recognition.face_landmarks(image)
    try:
        results = {
            'filename': filename,
            'right_eye': format_points(face_landmarks_list[0]['right_eye']),
            'left_eye': format_points(face_landmarks_list[0]['left_eye']),
            'top_lip': format_points(face_landmarks_list[0]['top_lip']),
            'nose_tip': format_points(face_landmarks_list[0]['nose_tip']),
            'left_eyebrow': format_points(face_landmarks_list[0]['left_eyebrow']),
            'bottom_lip': format_points(face_landmarks_list[0]['bottom_lip']),
            'right_eyebrow': format_points(face_landmarks_list[0]['right_eyebrow']),
            'chin': format_points(face_landmarks_list[0]['chin']),
            'nose_bridge': format_points(face_landmarks_list[0]['nose_bridge']),
            'status': 1
        }
    except Exception as e:
        results = {
            'filename': filename,
            'right_eye': [],
            'left_eye': [],
            'top_lip': [],
            'nose_tip': [],
            'left_eyebrow': [],
            'bottom_lip': [],
            'right_eyebrow': [],
            'chin': [],
            'nose_bridge': [],
            'status': 0
        }
    print (json.dumps(results))
