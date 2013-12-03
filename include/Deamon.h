/*
 * Deamon.h
 *
 *  Created on: 3 gru 2013
 *      Author: grzecho
 */

#ifndef DEAMON_H_
#define DEAMON_H_

class Deamon {
public:
    Deamon();
    virtual ~Deamon();
    static void demonize(void (*process)());
};

#endif /* DEAMON_H_ */
