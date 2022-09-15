.intel_syntax noprefix
.global scale
.text

scale:

	;rbx = x
	mov r8, rdi
	shr r8, 16
	movzx r8, r8w
	lea rax, [rdx]
	imul rax, r8
	xor rbx, rbx
	cmp r8, 1
	jl .Lend
	.L:

		;r10 = y
		mov r9, rdi
		shr r9, 32
		movzx r9, r9w
		xor r10, r10
		cmp r9, 1
		jl .Lweiter
		.L2:
			lea r11, [r10]
			imul r11, r8
			lea r11, [r11+rbx]
			imul r11, 3 

			/* xmm0 Register laden*/
			movzx r13, byte ptr [rsi+r11+2]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+1]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11]
			movq xmm0, r13
			movzx r13, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+3]
			mov [rsp-8], r13
			movhpd xmm0, [rsp-8]

			/* xmm2 Register laden */
			movzx r13, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+3]
			movq xmm2, r13
			movzx r13, byte ptr [rsi+r11+8]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+7]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+6]
			mov [rsp-8], r13
			movhpd xmm2, [rsp-8]
			lea r12, [r8+r8*2]
			lea r11, [r11+r12]

			/* xmm1 Register laden*/
			movzx r13, byte ptr [rsi+r11+2]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+1]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11]
			movq xmm1, r13
			movzx r13, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+3]
			mov [rsp-8], r13
			movhpd xmm1, [rsp-8]

			/* xmm3 Register laden*/
			movzx r13, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+3]
			movq xmm3, r13
			movzx r13, byte ptr [rsi+r11+8]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+7]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+6]
			mov [rsp-8], r13
			movhpd xmm3, [rsp-8]

			/* dx */
			xor r13, r13
			lea r12, [rdx+rdx*2-3]
			.L3:

				/* dy */
				xor r14, r14
				.L4:

					/* P(0,s)*dx und P(s,s)*dx */
					lea r15, [r13]
					lea r11, [r15]
					shl r11, 16
					mov r11w, r15w
					movd xmm6, r11d
					pshufd xmm6, xmm6, 0
					movdqu xmm7, xmm6
					pmullw xmm6, xmm2
					pmullw xmm7, xmm3

					/* P(s,0)*dy und P(s,s)*dy */
					lea r15, [r14]
					lea r11, [r15]
					shl r11, 16
					mov r11w, r15w
					movd xmm5, r11d
					pshufd xmm5, xmm5, 0
					movdqu xmm15, xmm5
					pmullw xmm5, xmm1
					pmullw xmm7, xmm15

					/* P(0,0)*(scaleFac-dx) und P(s,0)*(scaleFac-dx) */
					lea r15, [rdx]
					sub r15, r13
					lea r11, [r15]
					shl r11, 16
					mov r11w, r15w
					movd xmm4, r11d
					pshufd xmm4, xmm4, 0
					movdqu xmm13, xmm4
					pmullw xmm4, xmm0
					pmullw xmm5, xmm13

					/* P(0,0)*(scaleFac-dy) und P(0,s)*(scaleFac-dy) */
					lea r15, [rdx]
					sub r15, r14
					lea r11, [r15]
					shl r11, 16
					mov r11w, r15w
					movd xmm12, r11d
					pshufd xmm12, xmm12, 0
					movdqu xmm14, xmm12
					pmullw xmm4, xmm12
					pmullw xmm6, xmm14

					/* Aufsummieren */
					paddw xmm4, xmm5
					paddw xmm6, xmm7
					paddw xmm4, xmm6

					/* In den allokierten Speicherbereich laden */
					lea r15, [r10]
					imul r15, rdx
					lea r15, [r15+r14]
					imul r15, rax
					lea r11, [rbx]
					imul r11, rdx
					lea r11, [r11+r13]
					lea r15, [r15+r11]
					lea r15, [r15+r15*2]
					lea r11, [rdx]
					imul r11, r11
					push rax
					push rdx
					movups [rsp-16], xmm4
					movzx rax, word ptr[rsp-16]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-14]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-12]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+r12+1]
					movzx rax, word ptr [rsp-8]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-6]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-4]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					pop rdx
					pop rax
					
					lea r14, [r14+1]
					cmp r14, rdx
					jl .L4

				lea r13, [r13+1]
				cmp r13, rdx
				jl .L3

			lea r10, [r10+1]
			cmp r10, r9
			jl .L2

			/* Untere Randpixel behandeln */
			lea r12, [rax+rax*2]
			lea r11, [rdx-1]
			lea r14, [r11]
			imul r14, r12
			sub r15, r14
			lea r10, [rdx+rdx]
			lea r14, [r10+r10*2]
			sub r15, r14
			imul r10, 3
			.L5:
				lea r14, [rdx+rdx]
				.L6:
					mov r13, [rcx+r15]
					lea r15, [r15+r12]
					mov [rcx+r15], r13b
					shr r13, 8
					mov [rcx+r15+1], r13b
					shr r13, 8
					mov [rcx+r15+2], r13b
					lea r15, [r15+3]
					sub r15, r12
					dec r14
					jnz .L6
				sub r15, r10
				lea r15, [r15+r12]
				dec r11
				jnz .L5
				
		.Lweiter:
		lea rbx, [rbx+2]
		cmp rbx, r8
		jl .L

		/* Rechte Randpixel behandeln */
		lea rax, [r9]
		imul rax, rdx
		imul r8, rdx
		lea r12, [r8+r8*2]
		lea r10, [rdx-1]
		.L7:
			lea r9, [rax]
			imul r13, r10, 3
			neg r13
			lea r13, [r12+r13-3]
			.L8:
				mov rbx, [rcx+r13]
				lea r13, [r13+3]
				mov [rcx+r13], bl
				shr rbx, 8
				mov [rcx+r13+1], bl
				shr rbx, 8
				mov [rcx+r13+2], bl
				lea r13, [r13+r12-3]
				dec r9
				jnz .L8
			dec r10
			jnz .L7
	.Lend:
	ret
