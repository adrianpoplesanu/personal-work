using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using System.IO;

public class MainImageRenderer : MonoBehaviour {
    public string logoUrl;
    public SpriteRenderer target;
    public FileUploadHandler fileUploadHandler;
    public float maxWidth; // use this for always having the same max width or max height
    public float maxHeight; // use this for always having the same max width or max height
    public float textureWidth;
    public float textureHeight;

    void Start() {
        StartCoroutine(LoadImage());
    }

    IEnumerator LoadImage() {
        //UnityWebRequest www = UnityWebRequestTexture.GetTexture("http://ec2-52-91-25-4.compute-1.amazonaws.com:9191/logo.jpg");
        UnityWebRequest www = UnityWebRequestTexture.GetTexture(logoUrl);
        yield return www.SendWebRequest();

        if(www.isNetworkError || www.isHttpError) {
            Debug.Log(www.error);
        }
        else {
            Texture2D texture = ((DownloadHandlerTexture)www.downloadHandler).texture;
            //GetComponent<SpriteRenderer>().sprite = Sprite.Create(myTexture, new Rect(0, 0, myTexture.width, myTexture.height), new Vector2(0, 0));
            Sprite sprite = Sprite.Create(texture, new Rect(0, 0, texture.width, texture.height), Vector2.zero);
            target.sprite = sprite;
            Bounds bounds = target.sprite.bounds;
            float factorWidth = maxWidth / bounds.size.x;
            float factorHeight = maxHeight / bounds.size.y;
            float factor = Mathf.Min(factorWidth, factorHeight);
            transform.localScale = new Vector3(factor, factor, factor);
        }
    }

    public void RefreshImage(string path) {
        // upload file to server for image processing
        fileUploadHandler.ProcessImage(path);
        
        // do the phisical loading of a file from disk on the target sprite
        byte[] byteArray = File.ReadAllBytes(path);
        Texture2D texture = new Texture2D(8, 8);
        texture.LoadImage(byteArray);
        //img.sprite = Sprite.Create(texture, new Rect(0, 0, texture.width, texture.height), new Vector2(0, 0));
        textureWidth = texture.width;
        textureHeight = texture.height;
        Sprite sprite = Sprite.Create(texture, new Rect(0, 0, texture.width, texture.height), Vector2.zero);
        target.sprite = sprite;
        Bounds bounds = target.sprite.bounds;
        float factorWidth = maxWidth / bounds.size.x;
        float factorHeight = maxHeight / bounds.size.y;
        float factor = Mathf.Min(factorWidth, factorHeight);
        transform.localScale = new Vector3(factor, factor, factor);
    }
}
