
///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     shave class file 
///


// 1: Includes
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <mv_types.h>
#include <registersMyriad.h>
#include <DrvSvu.h>
#include <swcShaveLoader.h>
#include "Shave.h" 

Shave::Shave(unsigned int a){
	
	//printf("Shave constructur called for id:%d at 0x%x\n", a, this);
	this->id = a;
}

Shave::~Shave(){  

	//printf("Shave destructor called for %d at 0x%x\n", this->id, this);
}

Shave* Shave::handles[]={NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

Shave* Shave::gethandle(unsigned int a){

	Shave *obj;

	if (a>SHAVES_CNT){
		printf("Error: invalid shave ID\n");
		return NULL;
	}

	if (handles[a]==NULL){
		obj = new Shave(a);
		handles[a] = obj;
		
		return obj;
	}else{
		return handles[a];
	}

}

void Shave::destroy(unsigned int a){
	
	if (a>SHAVES_CNT){
		printf("Error: invalid shave ID\n");
		return;
	}

	if (handles[a]!=NULL){
		delete handles[a];
		handles[a]=NULL;
	}
}


void Shave::reset(void){

	swcResetShave(this->id);
}


void Shave::setdefaultstack(void){

	swcSetAbsoluteDefaultStack(this->id);

}

void Shave::start(unsigned int ptr){

	swcStartShave(this->id,ptr);
	this->busyflag = 1;
}

void Shave::wait(void){

	 swcWaitShave(this->id);
	 this->busyflag = 0;

}









