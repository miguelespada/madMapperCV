//
//  lemmings.h
//  lemmingsCV
//
//  Created by miguel valero espada on 12/4/12.
//
//

#ifndef lemmingsCV_lemmings_h
#define lemmingsCV_lemmings_h

class lemmings{
private:
    
#define FALL 1
#define WALK 0
    
    
    class lemming{
    public:
        ofVec2f pos;
        int alturaAnterior;
        int acc = 0;
        
        int imagen = 0;
        int modo;
        int imagenCaer = 4;
        
        
        ofImage walk[4];
        ofImage fall[2];
        int img = -1;
        ofSoundPlayer splat;
        
        lemming(int x, int y){
            pos.x = x;
            pos.y = y;
            alturaAnterior = pos.x;
            modo = FALL;
            acc = 0;
            
            walk[0].loadImage("l1.gif");
            
            walk[0].rotate90(-1);

            walk[1].loadImage("l3.gif");
            walk[1].rotate90(-1);
            walk[2].loadImage("l4.gif");
            walk[2].rotate90(-1);
            walk[3].loadImage("l5.gif");
            walk[3].rotate90(-1);
            fall[0].loadImage("lc1.gif");
            
            fall[0].rotate90(-1);
            fall[1].loadImage("lc2.gif");
            fall[1].rotate90(-1);
            splat.loadSound("SPLAT.WAV");
            
        }
        int distanciaSuelo(ofVec2f p, ofPixels pix ){
            int i;
            for(i = p.x - 5 ; i < pix.getWidth(); i++){
                int idx = (p.y * pix.getWidth()+ p.x) * pix.getBytesPerPixel();
                if( pix.getPixels()[idx] > 20) break;
            }
            return i;
        }
        
        void update( ofPixels pix){
            int altura = distanciaSuelo(pos, pix);
            if(modo == FALL){
                int distancia = altura- pos.x;
                if(distancia   <= 0){
                    if(acc > 100){
                        modo = - 1;
                        splat.play();
                    }
                    else{
                        modo = WALK;
                        acc = 0;
                    }
                }
                else{
                    pos.x += 5;
                    acc += 5;
                }
            }
            else if(modo == WALK){
                pos.y -= 5;
                
                int nAltura = distanciaSuelo(pos, pix);
                if(nAltura >=  pos.x + 10) {modo = FALL; pos.x += 5;}
                else pos.x = nAltura;
            }
            
            
        }
        void draw(){
            if(modo == WALK){
                img = (img + 1) % 4;
                walk[img].draw(pos.x - walk[img].getWidth() + 2, pos.y );
            }
            if(modo == FALL){
                img = (img + 1) % 2;
                fall[img].draw(pos.x  - walk[img].getWidth() + 2, pos.y);
            }
            
        }
    };

    
    
    vector<lemming> L;
    
    ofSoundPlayer music, letsgo;
    
    int mode = 0;
    int nLemmings = 0;
    int tasa = 8;
public:
    lemmings(){
        letsgo.loadSound("LETSGO.WAV");
        music.loadSound("a.mp3");
        ofSetFrameRate(10);
    }
    void update(int x, int y){
        if(nLemmings > 0 && ofGetFrameNum() % tasa == 0){
            lemming l(x, y);
            L.push_back(l);
            nLemmings --;
        }

    }
    void draw(ofPixels pix){
        
        for(int i = 0; i < L.size(); i++){
            L[i].update(pix);
            L[i].draw();
        }
    }
    void keyPressed(int key){
        if(key == ' '){
            if(mode == 0){
                nLemmings = 40;
                mode = 1;
                if(!music.getIsPlaying()) {
                    letsgo.play();
                    music.play();
                }
            }
            else if(mode == 1){
                nLemmings = 40;
                mode = 2;
                ofSetFrameRate(60);
                tasa = 3;
            }
            
            
            else if(mode == 2){
                nLemmings = 0;
                mode = 0;
                L.clear();
                ofSetFrameRate(10);
                tasa = 8;
                
                letsgo.stop();
                music.stop();
            }
        }
    }
};

#endif
