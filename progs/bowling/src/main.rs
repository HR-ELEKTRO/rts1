// remove next line in final version
#[allow(dead_code)]
#[derive(Debug, PartialEq)]
enum Error {
    InvalidFrame,
    GameAlreadyEnded,
}

// remove next line in final version
#[allow(dead_code)]
struct Frame {
    roll1: u32,
    roll2: u32,
}

// remove next line in final version
#[allow(dead_code)]
struct BowlingGame {
    frames: Vec<Frame>,
    current_frame: usize,
    score: u32,
    ended: bool,
}

// remove next line in final version
#[allow(dead_code)]
impl BowlingGame {
    fn new() -> BowlingGame {
        BowlingGame {
            frames: Vec::new(),
            current_frame: 0,
            score: 0,
            ended: false,
        }
    }

    fn frame(&mut self, roll1: u32, roll2: u32) -> Result<u32, Error> {
        if self.ended {
            return Err(Error::GameAlreadyEnded);
        }
        if self.current_frame <= 10 && roll1 + roll2 > 10 {
            return Err(Error::InvalidFrame);
        }
        Ok(0)
    }

    fn end_score(&self) -> u32 {
        if self.ended {
            0
        } else {
            self.score
        }
    }

}

#[test]
fn test_new_game() {
    let game = BowlingGame::new();
    assert_eq!(game.end_score(), 0);
}

#[test]
fn test_invalid_frame_1() {
    let mut game = BowlingGame::new();
    assert_eq!(game.frame(11, 0), Err(Error::InvalidFrame));
}

#[test]
fn test_invalid_frame_2() {
    let mut game = BowlingGame::new();
    assert_eq!(game.frame(5, 6), Err(Error::InvalidFrame));
}

#[test]
fn test_game_already_ended() {
    let mut game = BowlingGame::new();
    game.ended = true;
    assert_eq!(game.frame(1, 0), Err(Error::GameAlreadyEnded));
}

#[test]
fn test_frame_1() {
    let mut game = BowlingGame::new();
    assert_eq!(game.frame(1, 0), Ok(1));
}

#[test]
fn test_frame_2() {
    let mut game = BowlingGame::new();
    for _ in 0..10 {
        game.frame(1, 0).unwrap();
    }
    assert_eq!(game.end_score(), 10);
}

#[test]
fn test_game_not_ended() {
    let mut game = BowlingGame::new();
    game.frame(1, 0).unwrap();
    assert_eq!(game.end_score(), 0);
}

#[test]
fn test_spare() {
    let mut game = BowlingGame::new();
    assert_eq!(game.frame(5, 5), Ok(10));
    assert_eq!(game.frame(3, 2), Ok(18));
}

#[test]
fn test_strike() {
    let mut game = BowlingGame::new();
    assert_eq!(game.frame(10, 0), Ok(10));
    assert_eq!(game.frame(3, 2), Ok(20));
}

#[test]
fn test_strikes() {
    let mut game = BowlingGame::new();
    assert_eq!(game.frame(10, 0), Ok(10));
    assert_eq!(game.frame(10, 0), Ok(30));
    assert_eq!(game.frame(3, 2), Ok(43));
}

#[test]
fn test_last_illegal() {
    let mut game = BowlingGame::new();
    for _ in 0..10 {
        game.frame(1, 0).unwrap();
    }
    assert_eq!(game.frame(1, 0), Err(Error::InvalidFrame));
}

#[test]
fn test_last_spare_illegal() {
    let mut game = BowlingGame::new();
    for _ in 0..10 {
        game.frame(5, 5).unwrap();
    }
    assert_eq!(game.frame(5, 5), Err(Error::InvalidFrame));
}

#[test]
fn test_last_spare() {
    let mut game = BowlingGame::new();
    for _ in 0..10 {
        game.frame(5, 5).unwrap();
    }
    assert_eq!(game.frame(5, 0), Ok(150));
}

#[test]
fn test_last_strike() {
    let mut game = BowlingGame::new();
    for _ in 0..9 {
        game.frame(0, 0).unwrap();
    }
    assert_eq!(game.frame(10, 0), Ok(10));
    assert_eq!(game.frame(5, 5), Ok(20));
}

#[test]
fn test_frame_max() {
    let mut game = BowlingGame::new();
    for _ in 0..10 {
        game.frame(10, 0).unwrap();
    }
    // extra rolls because of last strike
    game.frame(10, 10).unwrap();
    assert_eq!(game.end_score(), 300);
}

fn main() {
    // code here;
}
