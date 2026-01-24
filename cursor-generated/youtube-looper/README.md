# YouTube Looper

A simple web application that allows you to embed and play YouTube videos with a continuous loop feature.

## Features

- Enter any YouTube URL and play it embedded
- Toggle loop mode to continuously replay the video
- Clean, modern UI with gradient design
- Responsive layout that works on different screen sizes

## How to Use

1. **Start a local web server** (required for YouTube API to work properly):
   ```bash
   python3 -m http.server 8000
   ```

2. **Open the application** in your browser:
   ```
   http://localhost:8000/index.html
   ```

3. **Enter a YouTube URL** in the input field (supports various YouTube URL formats)

4. **Click "Play"** to embed and start the video

5. **Click "Loop"** to toggle continuous playback on/off

## Supported URL Formats

The application supports various YouTube URL formats:
- `https://www.youtube.com/watch?v=VIDEO_ID`
- `https://youtu.be/VIDEO_ID`
- `https://www.youtube.com/embed/VIDEO_ID`
- URLs with additional parameters (playlists, timestamps, etc.)

## Files

- `index.html` - Main HTML structure
- `style.css` - Styling and layout
- `index.js` - YouTube API integration and functionality

## Note

Opening the HTML file directly from the file system (`file://` protocol) may cause issues with YouTube's iframe API due to security restrictions. Always use a local web server for best results.

