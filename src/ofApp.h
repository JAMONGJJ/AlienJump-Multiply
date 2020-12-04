#pragma once

#include "ofMain.h"
using namespace glm;

class ofApp : public ofBaseApp{

	public:
		float score;										// 게임 점수
		float hardness;								// 장애물 판정 난이도
		float timer;										// 점프 안내 메시지 타이머(5초 후 사라짐)
		float jumpSpeed;								// 점프 속도
		int fixedFrameRate;
		int frameNum[8];								// 점프할 때 속도감을 위해 곱하는 변수
		bool jumping[8];								// true : 점프 중, false : 점프 안하는 중
		bool canJump[8];								// true : 점프 가능, false : 점프 불가
		float frame;									// 매 프레임마다 스프라이트 시트 변경을 위한 변수
		float obstacleMove[8];						// 매 프레임마다 장애물이 이동하는 벡터의 x값
		float backgroundMove;						// 매 프레임마다 배경이 이동하는 벡터의 x값
		float **tmpHeight;							// 캐릭터가 점프할 때 올라가는 높이를 저장하는 배열
		vec3 charJumpPos[8];						// 점프 모션을 위해 shader로 전달되는 유니폼 변수
		vec3 characterInitialPosition;				// 캐릭터 위치
		vec3 obstacleInitialPosition[8];				// 장애물의 초기 위치
		
		bool gameStart;								// true : 게임 진행 중, false : 게임 시작 전
		bool gameOver;								// true : 게임 오버, false : 게임 진행 중
		int stage;										// 스테이지
		int scoreOffset[3] = { 70, 200, 600 };	// 각 점수를 넘으면 다음 Stage로 진입
		float obstacleResetOffset[8] = {			// 각 스테이지마다 장애물이 해당 x값보다 작아지면 위치 초기화
			-1.0f, -1.5f, -0.6f, -1.7f,
			 -0.7f, -0.3f, -1.4f, -1.3f};
		mat4 **modelArray;							// 각 스테이지마다 vertex Shader로 전해지는 변환행렬들을 저장하는 2차원행렬

		ofMesh charMesh[8];
		ofMesh obstacleMesh[8];
		ofMesh backgroundMesh;
		ofMesh gamestartTextMesh;
		ofMesh gameoverTextMesh;
		ofMesh restartTextMesh;
		ofMesh jumpNoticeMesh;
		ofMesh windowMesh;

		ofShader alphaTestShader;					// default Shader
		ofShader spritesheetShader;
		ofShader obstacleShader;
		ofShader repeatingShader;
		ofShader textShader;
		ofShader noticeShader;

		ofImage alienImg;
		ofImage backgroundImg;
		ofImage obstacleImg;
		ofImage gamestartTextImg;
		ofImage gameoverTextImg;
		ofImage restartTextImg;
		ofImage jumpNoticeImg[8];
		ofImage windowImg[3];

		bool Collide(float wA, float hA, glm::vec3 posA, float wB, float hB, glm::vec3 posB);	// 충돌감지함수
		void reset();								// 게임을 재시작할 때 모든 변수를 초기화하는 함수
		void buildPreset(int n);



		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
