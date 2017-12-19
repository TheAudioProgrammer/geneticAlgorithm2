#include "ofApp.h"





//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(0, 0);
    
    //create the creatures
    for (int i = 0; i < numGa; i++)
    {
        float ran = 0;
        for (int j = 0; j < numChroma; j++)
        {
            ran = int(ofRandom(0, 9));
            ga.push_back(ran);
        }
        allGa.push_back(ga);
        ga.clear();
    }
    
    //calculate fitnesses
    for (int i = 0; i < allGa.size(); i++)
    {
        float fitness = 0;
        float lastFitness = -1000;
        for (int j = 0; j < 1; j++)
        {
            //fitness function
            fitness = (allGa[i][j] + allGa[i][j + 1]) - (allGa[i][j + 2] + allGa[i][j + 3]) + (allGa[i][j + 4] + allGa[i][j + 5]) - (allGa[i][j + 6] + allGa[i][j + 7]);
            //std::cout <<fitness << std::endl;
        }
        fitnessScores.push_back(fitness);
    }

    
    //find worst fitness
    auto result = std::min_element (std::begin(fitnessScores), std::end(fitnessScores));
    worst = int(result - fitnessScores.begin());
    
    //find best fitness
    auto result2 = std::max_element (std::begin(fitnessScores), std::end(fitnessScores));
    best = int (result2 - fitnessScores.begin());
    
    
    //find second and third best (not very scalable)
    for (int i = 0; i < fitnessScores.size(); i++)
    {
        //std::cout << fitnessScores[i] << std::endl;
        
        for (int j = 0; j < i; j++)
        {
            if (i != worst && i != best)
            {
                if (j != worst && j != best)
                {
                    if (fitnessScores[i] > fitnessScores[j])
                    {
                        secondBest = i;
                        thirdBest = j;
                    } else
                    {
                        secondBest = j;
                        thirdBest = i;
                    }
                }
            }
        }
    }
    
    
    //make children
    for (int i = 0; i < 3; i++)
    {
        //temp vectors for children
        std::vector<int> temp1;
        std::vector<int> temp2;
        
        //children 1 & 2----- one point crossover
        if (i == 0)
        {
            for (int j = 0; j < 1; j++)
            {
                //chroma 0-3
                for (int k = 0; k < 4; k++)
                {
                    temp1.push_back(allGa[best][k]);
                    temp2.push_back(allGa [secondBest][k]);
                }
                //chroma 4-7
                for (int k = 4; k < numChroma; k++)
                {
                    temp1.push_back(allGa[secondBest][k]);
                    temp2.push_back(allGa[best][k]);
                }
            }
            //push into population
            allGa.push_back(temp1);
            allGa.push_back(temp2);
            
            //clear for next children
            temp1.clear();
            temp2.clear();
        }
        
        
        //children 3 & 4---- 2 point crossover
        if (i == 1)
        {
            //use 2nd and 3rd best parents
            for (int j = 2; j < 4; j++)
            {
                //chroma 0-1
                for (int k = 0; k < 2; k++)
                {
                    temp1.push_back(allGa[secondBest][k]);
                    temp2.push_back(allGa[thirdBest][k]);
                }
                //chroma 2-5
                for (int k = 2; k < 6; k++)
                {
                    temp1.push_back(allGa[thirdBest][k]);
                    temp2.push_back(allGa[secondBest][k]);
                }
                //chroma 6-7
                for (int k = 6; k < numChroma; k++)
                {
                    temp1.push_back(allGa[secondBest][k]);
                    temp2.push_back(allGa[thirdBest][k]);
                }
            }
            //push into population
            allGa.push_back(temp1);
            allGa.push_back(temp2);
            
            //clear for next children
            temp1.clear();
            temp2.clear();
        }
        
        //children 5 and 6---- uniform crossover
        if (i == 2)
        {
            //use 1st and 3rd best parents
            for (int j = 0; j < 1; j++)
            {
                //chroma 0-2
                for (int k = 0; k < 3; k++)
                {
                    temp1.push_back(allGa[best][k]);
                    temp2.push_back(allGa[thirdBest][k]);
                }
                //chroma 3-5
                for (int k = 3; k < 6; k++)
                {
                    temp1.push_back(allGa[thirdBest][k]);
                    temp2.push_back(allGa[best][k]);
                }
                //chroma 6-7
                for (int k = 6; k < numChroma; k++)
                {
                    temp1.push_back(allGa[best][k]);
                    temp2.push_back(allGa[thirdBest][k]);
                }
            }
            //push into population
            allGa.push_back(temp1);
            allGa.push_back(temp2);
            
            //clear for next children
            temp1.clear();
            temp2.clear();
        }
    }
    
    
    //clear all fitness scores to evaluate fitness
    fitnessScores.clear();
    
    //recalculate final fitnesses
    //calculate fitnesses
    for (int i = 0; i < allGa.size(); i++)
    {
        float fitness = 0;
        float lastFitness = -1000;
        for (int j = 0; j < 1; j++)
        {
            //fitness function
            fitness = (allGa[i][j] + allGa[i][j + 1]) - (allGa[i][j + 2] + allGa[i][j + 3]) + (allGa[i][j + 4] + allGa[i][j + 5]) - (allGa[i][j + 6] + allGa[i][j + 7]);
            //std::cout <<fitness << std::endl;
        }
        fitnessScores.push_back(fitness);
    }

    
    //console out final scores
    for (int i = 0; i < fitnessScores.size(); i++)
    {
        if (i == 4)
        {
            std::cout << "Children" << std::endl;
        }
        
        std:: cout << "Chromasome: " << i << " Chromosome fitness: " << fitnessScores[i] << std::endl;
    }
    
    
    
    
//    for (int i = 0; i < allGa.size(); i++)
//    {
//        for (int j = 0; j < numChroma; j++)
//        {
//            std::cout << "GA: " << i << " Chroma: " << allGa[i][j] << std::endl;
//        }
//    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
