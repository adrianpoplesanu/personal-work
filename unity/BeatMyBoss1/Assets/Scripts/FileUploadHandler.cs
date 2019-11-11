using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class FileUploadHandler : MonoBehaviour {
    public string uploadUrl;
    public ElementsCalculator elementsCalculator;

    public void ProcessImage(string path) {
        StartCoroutine(UploadFile(path));
    }

    private IEnumerator UploadFile(string path) {
        //List<IMultipartFormSection> formData = new List<IMultipartFormSection>();
        //formData.Add(new MultipartFormFileSection("file", path));

        byte[] byteArray = System.IO.File.ReadAllBytes(path);
        WWWForm formrequest = new WWWForm();
        formrequest.AddBinaryData("file", byteArray, "sashi.jpg", "image/jpeg"); // a lot of hardcoding here

        //UnityWebRequest www = UnityWebRequest.Post(uploadUrl, formData);
        UnityWebRequest www = UnityWebRequest.Post(uploadUrl, formrequest);
        yield return www.SendWebRequest();

        if (www.isNetworkError || www.isHttpError) {
            Debug.Log(www.error);
        } else {
            Debug.Log("Form upload complete!");
            HandleServerResponse(www.downloadHandler.text);
        }
    }

    private void HandleServerResponse(string responseBody) {
        Debug.Log(responseBody);
        DataJSONReasponse dataResponse = (DataJSONReasponse)JsonUtility.FromJson(responseBody, typeof (DataJSONReasponse));
        //Debug.Log(dataResponse);
        //Debug.Log(dataResponse.filename);
        //Debug.Log(dataResponse.right_eye);
        /*foreach (Point point in dataResponse.right_eye.points) {
            Debug.Log(point.values);
        }*/
        foreach (Point point in dataResponse.left_eye) {
            Debug.Log(point.x);
        }
        elementsCalculator.PlaceRightEye(dataResponse.right_eye);
        elementsCalculator.PlaceLeftEye(dataResponse.left_eye);
        //elementsCalculator.PlaceTopLip(dataResponse.top_lip);
        //elementsCalculator.PlaceNoseTip(dataResponse.nose_tip);
        //elementsCalculator.PlaceLeftEyebrow(dataResponse.left_eyebrow);
        //elementsCalculator.PlaceBottomLip(dataResponse.bottom_lip);
        //elementsCalculator.PlaceRightEyebrow(dataResponse.right_eyebrow);
        //elementsCalculator.PlaceChin(dataResponse.chin);
        //elementsCalculator.PlaceNoseBridge(dataResponse.nose_bridge);
    }
}

[System.Serializable]
public class Point {
    public float x, y;
}

[System.Serializable]
public class DataJSONReasponse {
    public string filename;
    public int status;
    public Point[] right_eye;
    public Point[] left_eye;
    public Point[] top_lip;
    public Point[] nose_tip;
    public Point[] left_eyebrow;
    public Point[] bottom_lip;
    public Point[] right_eyebrow;
    public Point[] chin;
    public Point[] nose_bridge;
}