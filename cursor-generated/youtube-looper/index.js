let player;
let isLooping = false;
let currentVideoId = null;
let apiReady = false;

// Wait for YouTube API to load
function onYouTubeIframeAPIReady() {
    apiReady = true;
}

// Extract YouTube video ID from URL
function extractVideoId(url) {
    const regExp = /^.*(youtu.be\/|v\/|u\/\w\/|embed\/|watch\?v=|&v=)([^#&?]*).*/;
    const match = url.match(regExp);
    return (match && match[2].length === 11) ? match[2] : null;
}

// Initialize or update the YouTube player
function initializePlayer(videoId) {
    const container = document.getElementById('videoContainer');
    
    // Clear existing content
    container.innerHTML = '<div id="youtube-player"></div>';
    
    // Build playerVars - only include origin if not using file:// protocol
    const playerVars = {
        autoplay: 1,
        controls: 1,
        rel: 0,
        modestbranding: 1,
        enablejsapi: 1
    };
    
    // Only add origin if not using file:// protocol (YouTube API doesn't like null origin)
    if (window.location.protocol !== 'file:') {
        playerVars.origin = window.location.origin;
    }
    
    // Initialize YouTube Player API - let it create the iframe
    player = new YT.Player('youtube-player', {
        videoId: videoId,
        width: '100%',
        height: '100%',
        playerVars: playerVars,
        events: {
            'onReady': onPlayerReady,
            'onStateChange': onPlayerStateChange,
            'onError': onPlayerError
        }
    });
    
    currentVideoId = videoId;
}

// Handle player ready event
function onPlayerReady(event) {
    // Player is ready, can now control it
    event.target.playVideo();
}

// Handle player errors
function onPlayerError(event) {
    console.error('YouTube Player Error:', event.data);
    alert('Error loading video. Please check the URL and try again.');
}

// Handle player state changes
function onPlayerStateChange(event) {
    // When video ends and looping is enabled, restart it
    if (event.data === YT.PlayerState.ENDED && isLooping && player) {
        try {
            player.seekTo(0);
            player.playVideo();
        } catch (e) {
            console.error('Error looping video:', e);
        }
    }
}

// Play button click handler
document.getElementById('playBtn').addEventListener('click', function() {
    const urlInput = document.getElementById('youtubeUrl');
    const url = urlInput.value.trim();
    
    if (!url) {
        alert('Please enter a YouTube URL');
        return;
    }
    
    const videoId = extractVideoId(url);
    
    if (!videoId) {
        alert('Invalid YouTube URL. Please enter a valid YouTube link.');
        return;
    }
    
    // Check if API is ready
    if (!apiReady && typeof YT === 'undefined') {
        alert('YouTube API is still loading. Please wait a moment and try again.');
        return;
    }
    
    // If player exists and it's the same video, just play it
    if (player && typeof player.playVideo === 'function' && currentVideoId === videoId) {
        try {
            player.playVideo();
        } catch (e) {
            console.error('Error playing video:', e);
            // Reinitialize if there's an error
            initializePlayer(videoId);
        }
    } else {
        // Otherwise, initialize new player
        initializePlayer(videoId);
    }
});

// Loop button click handler
document.getElementById('loopBtn').addEventListener('click', function() {
    isLooping = !isLooping;
    const loopBtn = document.getElementById('loopBtn');
    
    if (isLooping) {
        loopBtn.textContent = 'Loop: ON';
        loopBtn.classList.add('active');
    } else {
        loopBtn.textContent = 'Loop: OFF';
        loopBtn.classList.remove('active');
    }
});

// Allow Enter key to trigger play
document.getElementById('youtubeUrl').addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        document.getElementById('playBtn').click();
    }
});

