import sys
import face_recognition

if __name__ == '__main__':
    #filename = sys.argv[1]
    image = face_recognition.load_image_file("adri.jpg")
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
    print ('{{"filename": "{filename}", "right_eye": {right_eye}}}'.format(filename=results['filename'], right_eye=results['right_eye']))
