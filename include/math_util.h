#ifndef GUARD_MATH_UTIL_H
#define GUARD_MATH_UTIL_H

s16 MathUtil_Mul16(s16 x, s16 y);
s16 MathUtil_Mul16Shift(u8 s, s16 x, s16 y);
s32 MathUtil_Mul32(s32 x, s32 y);
s16 MathUtil_Div16(s16 x, s16 y);
s16 MathUtil_Div16Shift(u8 s, s16 x, s16 y);
s32 MathUtil_Div32(s32 x, s32 y);
s16 MathUtil_Inv16(s16 y);
s16 MathUtil_Inv16Shift(u8 s, s16 y);
s32 MathUtil_Inv32(s32 y);
s32 MathUtil_FindTrailingZeros(s32 n);
u32 MathUtil_GetFirstBitmaskFlag(s32 n);

#endif // GUARD_MATH_UTIL_H
