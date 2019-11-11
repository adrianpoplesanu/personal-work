using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ImageHolder : MonoBehaviour {
    public string url = "https://docs.unity3d.com/uploads/Main/ShadowIntro.png";

    IEnumerator Start() {
        Texture2D tex;
        tex = new Texture2D(4, 4, TextureFormat.DXT1, false);
        //tex = new Texture2D (2, 2, TextureFormat.BGRA32,false);
        using (WWW www = new WWW(url)) {
            yield return www;
            www.LoadImageIntoTexture(tex);
            GetComponent<Renderer>().material.mainTexture = tex;
            //GetComponent<Renderer>().material.SetTexture("_MainTex", tex);
            //GetComponent<Renderer>().material.SetTexture("_BaseMap", tex);
        }
    }
}
