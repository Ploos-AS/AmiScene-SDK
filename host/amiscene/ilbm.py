"""Dependency-free IFF ILBM reader/writer for scene asset workflows."""
import struct
def _chunk(cid,data):
 return cid+struct.pack(">I",len(data))+data+(b"\0" if len(data)&1 else b"")
def _byterun1_decode(data,expected):
 out=bytearray();i=0
 while i<len(data) and len(out)<expected:
  n=data[i];i+=1;n=n-256 if n>127 else n
  if 0<=n<=127:count=n+1;out+=data[i:i+count];i+=count
  elif -127<=n<=-1:
   count=1-n
   if i>=len(data):raise ValueError("truncated ByteRun1")
   out+=data[i:i+1]*count;i+=1
 if len(out)!=expected:raise ValueError("ByteRun1 size mismatch")
 return bytes(out)
def _byterun1_encode(data):
 out=bytearray();i=0
 while i<len(data):
  run=1
  while i+run<len(data) and data[i+run]==data[i] and run<128:run+=1
  if run>=3:out.append((1-run)&255);out.append(data[i]);i+=run;continue
  start=i;i+=run
  while i<len(data):
   run=1
   while i+run<len(data) and data[i+run]==data[i] and run<128:run+=1
   if run>=3 or i-start>=128:break
   i+=run
  literal=data[start:i][:128];out.append(len(literal)-1);out+=literal
 return bytes(out)
def dumps_ilbm(width,height,planes,data,palette,compression=1):
 rowbytes=((width+15)//16)*2;expected=rowbytes*height*planes
 if len(data)!=expected:raise ValueError("ILBM data size mismatch")
 if planes<1 or planes>8:raise ValueError("planes must be 1..8")
 bmhd=struct.pack(">HHhhBBBBHBBhh",width,height,0,0,planes,0,compression,0,0,10,11,width,height)
 cmap=b"".join(bytes(c) for c in palette)
 body=_byterun1_encode(data) if compression==1 else data
 if compression not in (0,1):raise ValueError("compression must be 0 or 1")
 payload=b"ILBM"+_chunk(b"BMHD",bmhd)+_chunk(b"CMAP",cmap)+_chunk(b"BODY",body)
 return b"FORM"+struct.pack(">I",len(payload))+payload
def write_ilbm(path,width,height,planes,data,palette,compression=1):
 open(path,"wb").write(dumps_ilbm(width,height,planes,data,palette,compression))
def loads_ilbm(data):
 if len(data)<12 or data[:4]!=b"FORM" or data[8:12]!=b"ILBM":raise ValueError("not an ILBM FORM")
 chunks={};pos=12
 while pos+8<=len(data):
  cid=data[pos:pos+4];size=struct.unpack(">I",data[pos+4:pos+8])[0];pos+=8;chunks[cid]=data[pos:pos+size];pos+=size+(size&1)
 if b"BMHD" not in chunks or b"BODY" not in chunks:raise ValueError("ILBM requires BMHD and BODY")
 bm=chunks[b"BMHD"]
 if len(bm)<20:raise ValueError("short BMHD")
 width,height,x,y,planes,masking,compression,pad,transparent,xasp,yasp,pagew,pageh=struct.unpack(">HHhhBBBBHBBhh",bm[:20])
 rowbytes=((width+15)//16)*2;stored=planes+(1 if masking==1 else 0);expected=rowbytes*height*stored
 body=chunks[b"BODY"]
 if compression==1:body=_byterun1_decode(body,expected)
 elif compression!=0:raise ValueError("unsupported ILBM compression")
 if len(body)<expected:raise ValueError("short ILBM BODY")
 cmap=chunks.get(b"CMAP",b"");palette=[tuple(cmap[i:i+3]) for i in range(0,len(cmap)-2,3)]
 out=bytearray()
 for y in range(height):
  base=y*rowbytes*stored
  for p in range(planes):out+=body[base+p*rowbytes:base+(p+1)*rowbytes]
 return {"width":width,"height":height,"planes":planes,"rowbytes":rowbytes,"palette":palette,"data":bytes(out),"compression":compression}
def load_ilbm(path):return loads_ilbm(open(path,"rb").read())
