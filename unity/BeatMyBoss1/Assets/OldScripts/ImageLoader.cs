using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;

public class ImageLoader : MonoBehaviour {
    // The output of the image
    public Image img;
 
    // The source image
    //public string url = "http://images.earthcam.com/ec_metros/ourcams/fridays.jpg";
    //public string url = "http://img1.joyreactor.com/pics/post/funny-pictures-art-roman-sculpture-4922267.jpeg";
    public string url = "http://ec2-52-91-25-4.compute-1.amazonaws.com:9191/logo.jpg";
    //public string url = "D:\Documents\unity\ramona1\adri.jpg";
 
    IEnumerator Start() {
        Debug.Log("here2");
        WWW www = new WWW(url);
        yield return www;
        img.sprite = Sprite.Create(www.texture, new Rect(0, 0, www.texture.width, www.texture.height), new Vector2(0, 0));
    }

    private void LoadImageProcessor() {
        Debug.Log("here");
        Debug.Log(url);
        //WWW www = new WWW(url);
        //yield return www;
        byte[] byteArray = File.ReadAllBytes(url);
        Texture2D texture = new Texture2D(8, 8);
        texture.LoadImage(byteArray);
        img.sprite = Sprite.Create(texture, new Rect(0, 0, texture.width, texture.height), new Vector2(0, 0));
    }

    public void RefreshImage() {
        LoadImageProcessor();
    }
}
