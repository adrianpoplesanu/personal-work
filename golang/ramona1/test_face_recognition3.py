import sys
import face_recognition

def format_points(points):
    print (points)
    formatted_points = []
    for point in points:
        formatted_points.append([point[0], point[1]])
    return formatted_points

if __name__ == '__main__':
    filename = sys.argv[1]
    image = face_recognition.load_image_file(filename)
    face_landmarks_list = face_recognition.face_landmarks(image)
    results = {
        'filename': filename,
        'right_eye': face_landmarks_list[0]['right_eye'],
        'left_eye': face_landmarks_list[0]['left_eye'],
        'top_lip': face_landmarks_list[0]['top_lip'],
        'nose_tip': face_landmarks_list[0]['nose_tip'],
        'left_eyebrow': face_landmarks_list[0]['left_eyebrow'],
        'bottom_lip': face_landmarks_list[0]['bottom_lip'],
        'right_eyebrow': face_landmarks_list[0]['right_eyebrow'],
        'chin': face_landmarks_list[0]['chin'],
        'nose_bridge': face_landmarks_list[0]['nose_bridge']
    }
    print ('{{"filename": "{filename}", "right_eye": {right_eye}}}'.format(filename=results['filename'], right_eye=format_points(results['right_eye'])))
