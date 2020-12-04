#pragma once

#include "ofMain.h"
using namespace glm;

class ofApp : public ofBaseApp{

	public:
		float score;										// ���� ����
		float hardness;								// ��ֹ� ���� ���̵�
		float timer;										// ���� �ȳ� �޽��� Ÿ�̸�(5�� �� �����)
		float jumpSpeed;								// ���� �ӵ�
		int fixedFrameRate;
		int frameNum[8];								// ������ �� �ӵ����� ���� ���ϴ� ����
		bool jumping[8];								// true : ���� ��, false : ���� ���ϴ� ��
		bool canJump[8];								// true : ���� ����, false : ���� �Ұ�
		float frame;									// �� �����Ӹ��� ��������Ʈ ��Ʈ ������ ���� ����
		float obstacleMove[8];						// �� �����Ӹ��� ��ֹ��� �̵��ϴ� ������ x��
		float backgroundMove;						// �� �����Ӹ��� ����� �̵��ϴ� ������ x��
		float **tmpHeight;							// ĳ���Ͱ� ������ �� �ö󰡴� ���̸� �����ϴ� �迭
		vec3 charJumpPos[8];						// ���� ����� ���� shader�� ���޵Ǵ� ������ ����
		vec3 characterInitialPosition;				// ĳ���� ��ġ
		vec3 obstacleInitialPosition[8];				// ��ֹ��� �ʱ� ��ġ
		
		bool gameStart;								// true : ���� ���� ��, false : ���� ���� ��
		bool gameOver;								// true : ���� ����, false : ���� ���� ��
		int stage;										// ��������
		int scoreOffset[3] = { 70, 200, 600 };	// �� ������ ������ ���� Stage�� ����
		float obstacleResetOffset[8] = {			// �� ������������ ��ֹ��� �ش� x������ �۾����� ��ġ �ʱ�ȭ
			-1.0f, -1.5f, -0.6f, -1.7f,
			 -0.7f, -0.3f, -1.4f, -1.3f};
		mat4 **modelArray;							// �� ������������ vertex Shader�� �������� ��ȯ��ĵ��� �����ϴ� 2�������

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

		bool Collide(float wA, float hA, glm::vec3 posA, float wB, float hB, glm::vec3 posB);	// �浹�����Լ�
		void reset();								// ������ ������� �� ��� ������ �ʱ�ȭ�ϴ� �Լ�
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
