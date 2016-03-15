/*
 * File:   TBlockingQueue.h
 * Author: Nate Bosscher
 *
 * Created on February 26, 2016, 8:35 PM
 */

#include <iostream>

#include <sstream>
#include <stdlib.h>

#include "../src/helpers/BlockingQueue.h"
#include "./Test.h"

using namespace std;

class TBlockingQueue : public Test{
public:
    
    bool test(){
        BlockingQueue<int> _bq("Test-1");
        BlockingQueue<int> *bq = &_bq;
        
        // update status
        testSegment();
        
        // test receiver timeout
        try{
            bq->take(1);
        }catch(BlockingQueueStatus status){
            if(status != BQ_TIMEOUT){
                ostringstream stringStream;
                stringStream << "should have timed out. Instead threw " << status;
                error = stringStream.str();
                
                return false;
            }
        }
        
        // update status
        testSegment();
        
        int send = rand();
        
        try{
            bq->put(&send);
        }catch(BlockingQueueStatus status){
            ostringstream stringStream;
            stringStream << "should have sent value. Instead threw " << status;
            error = stringStream.str();
            return false;
        }
        
        // update status
        testSegment();
        
        int value;
        
        try{
            value = bq->take();
        }catch(BlockingQueueStatus status){
            ostringstream stringStream;
            stringStream << "should have got value. Instead threw " << status;
            error = stringStream.str();
            return false;
        }
        
        if(value != send){
            ostringstream stringStream;
            stringStream << "should have got " << value << ". Instead got " << send;
            error = stringStream.str();
            
            return false;
        }
        
        return true;

    }
};