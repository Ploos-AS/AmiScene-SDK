import pytest
from amiscene.blit import descriptor,validate,bltcon0,bltsize,emit_asm
def test_copy_a_descriptor():
 d=descriptor(channels="ad",minterm=0xf0,width=20,height=256)
 assert bltcon0(d)==0x09f0
 assert bltsize(d)==0x4014
def test_cookie_cut_channels_and_minterm():
 d=descriptor(channels="abcd",minterm=0xca)
 assert bltcon0(d)==0x0fca
def test_masks_shifts_modulos_emit_readably():
 d=descriptor(ashift=3,bshift=7,afwm=0xff00,alwm=0x00ff,amod=-2,dmod=40)
 out=emit_asm(d,"Bob")
 assert "$39f0" in out and "$7000" in out and "$fffe" in out and "$0028" in out
def test_rejects_invalid_dimensions():
 with pytest.raises(ValueError):descriptor(width=65)
 with pytest.raises(ValueError):descriptor(height=0)
