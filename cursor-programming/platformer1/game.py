import pygame
import sys
import math

# Initialize Pygame
pygame.init()

# Constants
SCREEN_WIDTH = 1200
SCREEN_HEIGHT = 800
FPS = 60

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
GRAY = (128, 128, 128)
BROWN = (139, 69, 19)
YELLOW = (255, 255, 0)
ORANGE = (255, 165, 0)

# Physics constants
GRAVITY = 0.8
JUMP_STRENGTH = -15
PLAYER_SPEED = 5
COMPANION_SPEED = 3
MAX_DISTANCE = 200  # Maximum distance between player and companion
COMPANION_CATCHUP_SPEED = 6  # Speed when catching up
COMPANION_SPEED_MATCH_RATE = 0.7  # How quickly companion matches player speed (higher = faster matching)
COMPANION_JUMP_MULTIPLIER = 1.1  # Companion jumps higher than player (1.1 = 10% higher)


class Player:
    def __init__(self, x, y):
        self.width = 40
        self.height = 40
        self.x = x
        self.y = y
        self.vel_x = 0
        self.vel_y = 0
        self.on_ground = False
        self.color = BLUE
        self.just_jumped = False
        self.jump_x_position = None  # X position where player jumped
        
    def update(self, platforms):
        # Apply gravity
        self.vel_y += GRAVITY
        
        # Update horizontal position first
        self.x += self.vel_x
        
        # Check horizontal collisions
        for platform in platforms:
            if self.collides_with(platform):
                if self.vel_x > 0:  # Moving right
                    self.x = platform.x - self.width
                elif self.vel_x < 0:  # Moving left
                    self.x = platform.x + platform.width
                self.vel_x = 0
        
        # Keep player on screen (horizontal)
        if self.x < 0:
            self.x = 0
            self.vel_x = 0
        elif self.x > SCREEN_WIDTH - self.width:
            self.x = SCREEN_WIDTH - self.width
            self.vel_x = 0
        
        # Update vertical position
        self.y += self.vel_y
        
        # Check vertical collisions
        self.on_ground = False
        for platform in platforms:
            if self.collides_with(platform):
                # Calculate overlap to determine collision side
                overlap_top = (self.y + self.height) - platform.y
                overlap_bottom = (platform.y + platform.height) - self.y
                
                if overlap_top < overlap_bottom and self.vel_y >= 0:
                    # Landing on top of platform
                    self.y = platform.y - self.height
                    self.vel_y = 0
                    self.on_ground = True
                elif overlap_bottom < overlap_top and self.vel_y <= 0:
                    # Hitting bottom of platform
                    self.y = platform.y + platform.height
                    self.vel_y = 0
        
        # Apply friction
        self.vel_x *= 0.8
        
        # Reset jump flag at end of update (after it's been used)
        self.just_jumped = False
        
    def collides_with(self, platform):
        return (self.x < platform.x + platform.width and
                self.x + self.width > platform.x and
                self.y < platform.y + platform.height and
                self.y + self.height > platform.y)
    
    def jump(self):
        if self.on_ground:
            self.vel_y = JUMP_STRENGTH
            self.on_ground = False
            self.just_jumped = True
            # Store the x position where player jumped
            self.jump_x_position = self.x + self.width // 2
    
    def move_left(self):
        self.vel_x = -PLAYER_SPEED
    
    def move_right(self):
        self.vel_x = PLAYER_SPEED
    
    def draw(self, screen):
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.width, self.height))
        # Draw eyes
        pygame.draw.circle(screen, WHITE, (int(self.x + 10), int(self.y + 15)), 5)
        pygame.draw.circle(screen, WHITE, (int(self.x + 30), int(self.y + 15)), 5)
        pygame.draw.circle(screen, BLACK, (int(self.x + 10), int(self.y + 15)), 2)
        pygame.draw.circle(screen, BLACK, (int(self.x + 30), int(self.y + 15)), 2)


class Companion:
    def __init__(self, x, y):
        self.width = 30
        self.height = 30
        self.x = x
        self.y = y
        self.vel_x = 0
        self.vel_y = 0
        self.on_ground = False
        self.color = YELLOW
        self.current_speed = 0  # Track current horizontal speed for matching
        
    def update(self, target_x, target_y, platforms, player_vel_x=0, player_jump_x=None, player_is_moving=False):
        # Apply gravity
        self.vel_y += GRAVITY
        
        # Calculate direction to target (player)
        companion_center_x = self.x + self.width // 2
        dx = target_x - companion_center_x
        dy = target_y - (self.y + self.height // 2)
        distance = math.sqrt(dx**2 + dy**2)
        
        # Check if companion should jump at player's jump position
        should_jump = False
        jump_position_passed = False
        if player_jump_x is not None and self.on_ground:
            # Check if companion has reached the jump position (within a small threshold)
            jump_threshold = 20
            distance_to_jump_x = companion_center_x - player_jump_x
            
            # Check if we've passed the jump position (moved past it)
            # This depends on which direction we're moving
            if abs(distance_to_jump_x) < jump_threshold:
                # Close enough to jump
                should_jump = True
                self.vel_y = JUMP_STRENGTH * COMPANION_JUMP_MULTIPLIER
                self.on_ground = False
                jump_position_passed = True
            elif (self.vel_x > 0 and distance_to_jump_x > jump_threshold) or \
                 (self.vel_x < 0 and distance_to_jump_x < -jump_threshold):
                # We've passed the jump position
                jump_position_passed = True
        
        # Calculate desired speed based on distance and player state
        desired_speed = 0
        
        # Define a threshold for when to start catching up aggressively (80% of max distance)
        CATCHUP_THRESHOLD = MAX_DISTANCE * 0.2
        
        if distance > MAX_DISTANCE:
            # Too far - catch up quickly
            if abs(dx) > 0:
                desired_speed = (dx / abs(dx)) * COMPANION_CATCHUP_SPEED
                self.current_speed = desired_speed
        elif distance > CATCHUP_THRESHOLD:
            # Approaching max distance - catch up aggressively to prevent falling back too far
            if abs(dx) > 0:
                desired_speed = (dx / abs(dx)) * COMPANION_CATCHUP_SPEED
                self.current_speed = desired_speed
        elif not player_is_moving and distance > 20:
            # Player stopped - catch up to player
            if abs(dx) > 0:
                desired_speed = (dx / abs(dx)) * COMPANION_CATCHUP_SPEED
                self.current_speed = desired_speed
        elif distance > 20:
            # Far enough - match player speed gradually
            if abs(player_vel_x) > 0.1:
                target_speed = player_vel_x
                self.current_speed = target_speed
                desired_speed = self.current_speed
            else:
                # Player moving slowly or stopped, use normal follow speed
                if abs(dx) > 0:
                    desired_speed = (dx / abs(dx)) * COMPANION_SPEED
                    self.current_speed = desired_speed
        else:
            # Close enough (within 50 pixels) - slow down gradually
            if abs(dx) > 0:
                # Still move slightly towards player but slower
                desired_speed = (dx / abs(dx)) * COMPANION_SPEED * 0.3
            else:
                desired_speed = 0
            self.current_speed = desired_speed
        
        # Apply horizontal movement
        self.vel_x = desired_speed
        
        # Update horizontal position first
        self.x += self.vel_x
        
        # Check horizontal collisions
        for platform in platforms:
            if self.collides_with(platform):
                if self.vel_x > 0:  # Moving right
                    self.x = platform.x - self.width
                elif self.vel_x < 0:  # Moving left
                    self.x = platform.x + platform.width
                self.vel_x = 0
        
        # Keep companion on screen
        if self.x < 0:
            self.x = 0
            self.vel_x = 0
        elif self.x > SCREEN_WIDTH - self.width:
            self.x = SCREEN_WIDTH - self.width
            self.vel_x = 0
        
        # Update vertical position
        self.y += self.vel_y
        
        # Check vertical collisions
        self.on_ground = False
        for platform in platforms:
            if self.collides_with(platform):
                # Calculate overlap to determine collision side
                overlap_top = (self.y + self.height) - platform.y
                overlap_bottom = (platform.y + platform.height) - self.y
                
                if overlap_top < overlap_bottom and self.vel_y >= 0:
                    # Landing on top of platform
                    self.y = platform.y - self.height
                    self.vel_y = 0
                    self.on_ground = True
                elif overlap_bottom < overlap_top and self.vel_y <= 0:
                    # Hitting bottom of platform
                    self.y = platform.y + platform.height
                    self.vel_y = 0
        
        # Apply friction
        self.vel_x *= 0.8
        
        # Return whether jump position was passed (for clearing it)
        return jump_position_passed
        
    def collides_with(self, platform):
        return (self.x < platform.x + platform.width and
                self.x + self.width > platform.x and
                self.y < platform.y + platform.height and
                self.y + self.height > platform.y)
    
    def draw(self, screen):
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.width, self.height))
        # Draw eyes
        pygame.draw.circle(screen, BLACK, (int(self.x + 8), int(self.y + 12)), 3)
        pygame.draw.circle(screen, BLACK, (int(self.x + 22), int(self.y + 12)), 3)


class Platform:
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = BROWN
        
    def draw(self, screen):
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.width, self.height))
        # Add some detail
        pygame.draw.rect(screen, BLACK, (self.x, self.y, self.width, self.height), 2)


class Game:
    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("2D Platformer - Player & Companion")
        self.clock = pygame.time.Clock()
        self.running = True
        
        # Create player
        self.player = Player(100, 100)
        
        # Create companion (start near player)
        self.companion = Companion(150, 100)
        
        # Create platforms
        self.platforms = [
            Platform(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 40),  # Ground
            Platform(200, SCREEN_HEIGHT - 150, 200, 20),
            Platform(500, SCREEN_HEIGHT - 250, 200, 20),
            Platform(800, SCREEN_HEIGHT - 350, 200, 20),
            Platform(300, SCREEN_HEIGHT - 450, 150, 20),
            Platform(700, SCREEN_HEIGHT - 550, 150, 20),
        ]
    
    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE or event.key == pygame.K_UP:
                    self.player.jump()
    
    def update(self):
        keys = pygame.key.get_pressed()
        
        # Track if player is moving
        player_is_moving = (keys[pygame.K_LEFT] or keys[pygame.K_a] or 
                           keys[pygame.K_RIGHT] or keys[pygame.K_d])
        
        # Player movement
        if keys[pygame.K_LEFT] or keys[pygame.K_a]:
            self.player.move_left()
        if keys[pygame.K_RIGHT] or keys[pygame.K_d]:
            self.player.move_right()
        
        # Store player jump position before updating
        player_jump_x = self.player.jump_x_position
        
        # Update game objects
        self.player.update(self.platforms)
        
        # Get player's current velocity after update
        player_vel_x = self.player.vel_x
        
        # Clear jump position if player has landed (reset for next jump)
        if self.player.on_ground:
            self.player.jump_x_position = None
        
        # Companion follows player
        player_center_x = self.player.x + self.player.width // 2
        player_center_y = self.player.y + self.player.height // 2
        jump_position_passed = self.companion.update(player_center_x, player_center_y, self.platforms, 
                                                     player_vel_x, player_jump_x, player_is_moving)
        
        # Clear jump position if companion has passed it
        if jump_position_passed:
            self.player.jump_x_position = None
    
    def draw(self):
        self.screen.fill((135, 206, 235))  # Sky blue background
        
        # Draw platforms
        for platform in self.platforms:
            platform.draw(self.screen)
        
        # Draw player and companion
        self.player.draw(self.screen)
        self.companion.draw(self.screen)
        
        # Draw instructions
        font = pygame.font.Font(None, 36)
        text = font.render("Arrow Keys / WASD: Move | Space/Up: Jump", True, BLACK)
        self.screen.blit(text, (10, 10))
        
        pygame.display.flip()
    
    def run(self):
        while self.running:
            self.handle_events()
            self.update()
            self.draw()
            self.clock.tick(FPS)
        
        pygame.quit()
        sys.exit()


if __name__ == "__main__":
    game = Game()
    game.run()

