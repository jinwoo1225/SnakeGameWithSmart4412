# SnakeGameWithSmart4412
### Hybus-Smart4412 교육용장비를 위한 cpp코딩

## Hybus-Smart4412장비에 Snake게임을 구현했습니다!
Snake게임이란?

https://en.wikipedia.org/wiki/Snake_(video_game_genre)

![Pic](./Pic/OnPlay.jpg)
### 사용한 IO장치
![Pic2](./Pic/Overview.jpg)
1. DotMatrix      "/dev/dot"
2. TactSwitch     "/dev/tactsw"
3. Character LCD  "/dev/clcd"
4. LED 8EA        "/dev/led"
5. FND 4EA        "/dev/fnd"

### 사용한 프로그래밍 언어
C/C++
### 플레이 영상 (클릭)
[![Watch the video](https://img.youtube.com/vi/Rp65Z1loa4c/hqdefault.jpg)](https://youtu.be/Rp65Z1loa4c)
### 플레이 방법
1. Hybus에 arm-linux-gnuaebi-g++로 컴파일된 프로그램을 적재
2. 프로그램 실행
3. 왼쪽에서 두번째 위에서 두번째에 있는 가운데 버튼으로 시작
4. 이동하려는 방향키로 Snake 이동 시작, 상하좌우는 가운데 버튼을 기준으로 구성되어있음.
5. 자신의 꼬리와 부딪혀서는 안되고, 벽과도 부딪히면 게임 오버
6. 게임오버가 되면 현재 점수가 표출되고, 5초뒤에 3번으로 이동 게임 재시작
7. 재시작하면 전에 플레이 했던 최고점수 표출

### 제한요소 1
1. IO장치를 동시에 접근하면 오류가 발생을 한다.
2. CLCD에 입력 시간이 존재한다.

### 해결방법 1
1. 1초를 30등분하여서 표시(30- ⍺)fps로 표시 각 수행과정에서 한프레임이 길어지게됨.
2. Tact Switch와 다른 장치들의 신호르 이용할때에는 매트릭스르 사용하지 않을때 사용.
3. CLCD는 초기화 하지않으면 값이 남아있으므로 점수에 변경이 있을때 새로고침
