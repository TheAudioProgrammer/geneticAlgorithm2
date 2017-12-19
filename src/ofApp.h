#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
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
    
    
    //number of chromasomes each
    int numChroma = 8;
    
    
    int variation = 9;
    
    //number of creatures
    int numGa = 4;
    
    int numChildren = 6;
    
    //stores the creatures
    std::vector <int> ga;
    
    //stores all creatures
    std::vector <std::vector <int>> allGa;
    
    //stores fitness scores
    std::vector <int> fitnessScores;
    
    int best, secondBest, thirdBest, worst;
    
    
		
};
