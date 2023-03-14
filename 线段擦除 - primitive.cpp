float delay, s_trim, e_trim;
string lengthuv_atbname = chs("length_uv_attrib_name");
delay = chf('delay');
s_trim = chf('Start_trim', @Time - delay);
e_trim = chf('End_trim', @Time - delay);

function void curve_trim(int primnum;float s_trim,e_trim;string lengthuv_atbname){

    int primpts[] = primpoints(0,primnum);
    
    int s_ptidx, e_ptidx;
    s_ptidx = -1;
    e_ptidx = -1;
    for(int i = 0; i<len(primpts); i++){
        vector arcuv = point(0, lengthuv_atbname, primpts[i]);
    
        if(s_ptidx == -1){
            if(arcuv[0] <= s_trim){
                s_ptidx = primpts[i];
            }
        }else{
            if(arcuv[0] <= s_trim){
                removepoint(0,primpts[i]);
            }
        }
        if(e_ptidx == -1){
            if(arcuv[0] >= e_trim){
                e_ptidx = primpts[i];
            }
        }else{
            if(arcuv[0] >= e_trim){
                removepoint(0,primpts[i]);
            }
        }
    }
    vector s_ptpos,e_ptpos;
    s_ptpos = primuv(0, "P", primnum, set(s_trim,0,0));
    e_ptpos = primuv(0, "P", primnum, set(e_trim,0,0));
    
    if(e_ptidx!=-1){
        setpointattrib(0,"P",s_ptidx,s_ptpos);
        setpointattrib(0, lengthuv_atbname, s_ptidx, s_trim);
    }
    if(e_ptidx!=-1){
        setpointattrib(0,"P",e_ptidx,e_ptpos);
        setpointattrib(0, lengthuv_atbname, e_ptidx, e_trim);
    }

}

curve_trim(@primnum,s_trim,e_trim,lengthuv_atbname);
