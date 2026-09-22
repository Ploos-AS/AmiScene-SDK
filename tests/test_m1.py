import unittest
from host.amiscene.table import sine,cosine,emit_asm
from host.amiscene.bitplane import chunky_to_planar,interleave,emit_asm as emit_bitmap_asm,emit_incbin
class T(unittest.TestCase):
 def test_sine(self):self.assertEqual(sine(4,100),[0,100,0,-100])
 def test_cos(self):self.assertEqual(cosine(4,100),[100,0,-100,0])
 def test_table_asm(self):self.assertIn("tbl_size equ",emit_asm([1,-1],"tbl"))
 def test_planar(self):self.assertEqual(chunky_to_planar([1,0,1,0,0,0,0,1],8,1,1),[bytes([0xA1])])
 def test_two(self):self.assertEqual(chunky_to_planar([0,1,2,3,0,1,2,3],8,1,2),[bytes([0x55]),bytes([0x33])])
 def test_interleave(self):self.assertEqual(interleave([bytes([1,2]),bytes([17,18])]),bytes([1,17,2,18]))
 def test_bitmap_asm(self):self.assertIn("dc.b $a1",emit_bitmap_asm(bytes([0xA1]),"pic"))
 def test_incbin(self):self.assertIn('incbin "pic.bin"',emit_incbin("pic.bin","pic"))
if __name__=="__main__":unittest.main()
