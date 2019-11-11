using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ElementsCalculator : MonoBehaviour {
    public MainImageRenderer mainImageRenderer;
    public SpriteRenderer spriteRenderer;
    public GameObject right_eye;
    public GameObject left_eye;
    public GameObject top_lip;
    public GameObject nose_tip;
    public GameObject left_eyebrow;
    public GameObject bottom_lip;
    public GameObject right_eyebrow;
    public GameObject chin;
    public GameObject nose_bridge;

    public void PlaceRightEye(Point[] points) {
        PlaceAllPoints(points);
        return;        
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        //Debug.Log("X = " + x);
        //Debug.Log("Y = " + y);
        right_eye.transform.position = new Vector2(x, y);
        //spriteRenderer.size.x
        //mainImageRenderer.textureWidth
        // mainImageRenderer.textureWidth ... spriteRenderer.size.x
        // eye.x ... x
    }

    public void PlaceLeftEye(Point[] points) {
        PlaceAllPoints(points);
        return;
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        left_eye.transform.position = new Vector2(x, y);
    }

    public void PlaceTopLip(Point[] points) {
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        top_lip.transform.position = new Vector2(x, y);
    }

    public void PlaceNoseTip(Point[] points) {
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        nose_tip.transform.position = new Vector2(x, y);
    }

    public void PlaceLeftEyebrow(Point[] points) {
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        left_eyebrow.transform.position = new Vector2(x, y);
    }

    public void PlaceBottomLip(Point[] points) {
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        bottom_lip.transform.position = new Vector2(x, y);
    }

    public void PlaceRightEyebrow(Point[] points) {
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        right_eyebrow.transform.position = new Vector2(x, y);
    }

    public void PlaceChin(Point[] points) {
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        chin.transform.position = new Vector2(x, y);
    }

    public void PlaceNoseBridge(Point[] points) {
        Point eye = points[0];
        float x = (spriteRenderer.size.x * eye.x / mainImageRenderer.textureWidth) - 2.32f;
        float y = (spriteRenderer.size.y * eye.y / mainImageRenderer.textureHeight) - 1.5f;
        nose_bridge.transform.position = new Vector2(x, y);
    }

    public void PlaceAllPoints(Point[] points) {
        foreach (Point point in points) {
            GameObject obj = Instantiate(right_eye);
            float x = (spriteRenderer.size.x * point.x / mainImageRenderer.textureWidth) - 2.32f - 1.3f;
            float y = (spriteRenderer.size.y * point.y / mainImageRenderer.textureHeight) - 1.5f - 0.35f;
            obj.transform.position = new Vector2(x, y);
        }
    }
}
