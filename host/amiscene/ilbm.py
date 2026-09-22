"""Minimal dependency-free IFF ILBM reader for scene asset workflows."""
import struct
def _byterun1(data,expected):
 out=bytearray();i=0
 while i<len(data) and len(out)<expected:
  n=data[i];i+=1;n=n-256 if n>127 else n
  if 0<=n<=127: count=n+1;out+=data[i:i+count];i+=count
  elif -127<=n<=-1:
   count=1-n
   if i>=len(data):raise ValueError("truncated ByteRun1")
   out+=data[i:i+1]*count;i+=1
 if len(out)!=expected:raise ValueError("ByteRun1 size mismatch")
 return bytes(out)
def load_ilbm(path):
 data=open(path,"rb").read()
 if len(data)<12 or data[:4]!=b"FORM" or data[8:12]!=b"ILBM":raise ValueError("not an ILBM FORM")
 chunks={};pos=12
 while pos+8<=len(data):
  cid=data[pos:pos+4];size=struct.unpack(">I",data[pos+4:pos+8])[0];pos+=8
  chunks[cid]=data[pos:pos+size];pos+=size+(size&1)
 if b"BMHD" not in chunks or b"BODY" not in chunks:raise ValueError("ILBM requires BMHD and BODY")
 bm=chunks[b"BMHD"]
 if len(bm)<20:raise ValueError("short BMHD")
 width,height,x,y,planes,masking,compression,pad,transparent,xasp,yasp,pagew,pageh=struct.unpack(">HHhhBBBBHBBhh",bm[:20])
 if planes<1 or planes>8:raise ValueError("unsupported ILBM plane count")
 rowbytes=((width+15)//16)*2; stored_planes=planes+(1 if masking==1 else 0); expected=rowbytes*height*stored_planes
 body=chunks[b"BODY"];body=_byterun1(body,expected) if compression==1 else body
 if compression not in (0,1):raise ValueError("unsupported ILBM compression")
 if len(body)<expected:raise ValueError("short ILBM BODY")
 palette=[];cmap=chunks.get(b"CMAP",b"")
 for i in range(0,len(cmap)-2,3):palette.append(tuple(cmap[i:i+3]))
 # BODY is row-interleaved by plane. Strip optional mask plane.
 out=bytearray()
 for yy in range(height):
  base=yy*rowbytes*stored_planes
  for p in range(planes):out+=body[base+p*rowbytes:base+(p+1)*rowbytes]
 return {"width":width,"height":height,"planes":planes,"rowbytes":rowbytes,"palette":palette,"data":bytes(out),"compression":compression}
