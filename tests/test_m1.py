import unittest
from host.amiscene.table import sine, cosine, emit_asm
from host.amiscene.bitplane import chunky_to_planar, interleave

class TableTests(unittest.TestCase):
    def test_sine(self): self.assertEqual(sine(4,100),[0,100,0,-100])
    def test_cosine(self): self.assertEqual(cosine(4,100),[100,0,-100,0])
    def test_asm(self): self.assertIn("tbl:\n    dc.w 1",emit_asm([1,-1],"tbl"))

class BitplaneTests(unittest.TestCase):
    def test_one_plane(self):
        self.assertEqual(chunky_to_planar([1,0,1,0,0,0,0,1],8,1,1),[bytes([0xA1])])
    def test_two_planes(self):
        self.assertEqual(chunky_to_planar([0,1,2,3,0,1,2,3],8,1,2),[bytes([0x55]),bytes([0x33])])
    def test_interleave(self):
        self.assertEqual(interleave([bytes([1,2]),bytes([17,18])]),bytes([1,17,2,18]))

if __name__=="__main__": unittest.main()
