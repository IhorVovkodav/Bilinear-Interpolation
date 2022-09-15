.intel_syntax noprefix
.global scale_256
.text

scale_256:
	;rbx = x
	mov r8, rdi
	shr r8, 16
	movzx r8, r8w
	xor rbx, rbx
	loop2:
		;r10 = y
		mov r9, rdi
		shr r9, 32
		movzx r9, r9w
		lea rax, [rdx]
		imul rax, r9
		xor r10, r10
		cmp r9, 1
		jl weiter
		loop3:
			lea r11, [r10]
			imul r11, r9
			lea r11, [r11+rbx]
			imul r11, 3
			movzx r13, byte ptr [rsi+r11+3]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+2]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+1]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11]
			movq xmm0, r13
			movzx r13, byte ptr [rsi+r11+7]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+6]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			mov [rsp-8], r13
			movhpd xmm0, [rsp-8]
			movdqu [rsp-32], xmm0
			movzx r13, byte ptr [rsi+r11+11]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+10]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+9]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+8]
			movq xmm0, r13
			movzx r13, byte ptr [rsi+r11+14]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+13]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+12]
			mov [rsp-8], r13
			movhpd xmm0, [rsp-8]
			movdqu [rsp-16], xmm0
			vmovdqu ymm0, [rsp-32]
			movzx r13, byte ptr [rsi+r11+6]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+3]
			movq xmm2, r13
			movzx r13, byte ptr [rsi+r11+10]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+9]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+8]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+7]
			mov [rsp-8], r13
			movhpd xmm2, [rsp-8]
			movdqu [rsp-32], xmm2
			movzx r13, byte ptr [rsi+r11+14]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+13]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+12]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+11]
			movq xmm2, r13
			movzx r13, byte ptr [rsi+r11+17]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+16]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+15]
			mov [rsp-8], r13
			movhpd xmm2, [rsp-8]
			movdqu [rsp-16], xmm2
			vmovdqu ymm2, [rsp-32]
			lea r12, [r9+r9*2]
			lea r11, [r11+r12]
			movzx r13, byte ptr [rsi+r11+3]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+2]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+1]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11]
			movq xmm1, r13
			movzx r13, byte ptr [rsi+r11+7]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+6]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			mov [rsp-8], r13
			movhpd xmm1, [rsp-8]
			movdqu [rsp-32], xmm1
			movzx r13, byte ptr [rsi+r11+11]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+10]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+9]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+8]
			movq xmm1, r13
			movzx r13, byte ptr [rsi+r11+14]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+13]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+12]
			mov [rsp-8], r13
			movhpd xmm1, [rsp-8]
			movdqu [rsp-16], xmm1
			vmovdqu ymm1, [rsp-32]
			movzx r13, byte ptr [rsi+r11+6]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+5]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+4]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+3]
			movq xmm3, r13
			movzx r13, byte ptr [rsi+r11+10]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+9]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+8]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+7]
			mov [rsp-8], r13
			movhpd xmm3, [rsp-8]
			movdqu [rsp-32], xmm3
			movzx r13, byte ptr [rsi+r11+14]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+13]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+12]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+11]
			movq xmm3, r13
			movzx r13, byte ptr [rsi+r11+17]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+16]
			shl r13, 16
			movzx r13w, byte ptr [rsi+r11+15]
			mov [rsp-8], r13
			movhpd xmm3, [rsp-8]
			movdqu [rsp-16], xmm3
			vmovdqu ymm3, [rsp-32]
			xor r13, r13
			lea r12, [rdx+rdx*2-3]
			loop4:
				xor r14, r14
				loop5:
					vmovdqu ymm4, ymm0
					vmovdqu ymm5, ymm1
					vmovdqu ymm6, ymm2
					vmovdqu ymm7, ymm3
					lea r15, [r13]
					movzx r11, r15b
					shl r15, 16
					mov r15b, r11b
					movd xmm6, r15d
					pshufd  xmm6, xmm6, 0
					movdqu [rsp-16], xmm6
					vbroadcasti128 ymm6, [rsp-16]
					vmovdqu ymm7, ymm6
					vpmullw ymm6, ymm6, ymm2
					vpmullw ymm7, ymm7, ymm3
					vmovdqu ymm14, ymm6
					vmovdqu ymm15, ymm7
					lea r15, [r14]
					movzx r11, r15b
					shl r15, 16
					mov r15b, r11b
					movd xmm5, r15d
					pshufd  xmm5, xmm5, 0
					movdqu [rsp-16], xmm5
					vbroadcasti128 ymm5, [rsp-16]
					vmovdqu ymm7, ymm5
					vpmullw ymm5, ymm5, ymm1
					vpmullw ymm7, ymm7, ymm15
					weiter3:
					vmovdqu ymm13, ymm5
					lea r15, [rdx]
					sub r15, r13
					movzx r11, r15b
					shl r15, 16
					mov r15b, r11b
					movd xmm4, r15d
					pshufd  xmm4, xmm4, 0
					movdqu [rsp-16], xmm4
					vbroadcasti128 ymm4, [rsp-16]
					vmovdqu ymm5, ymm4
					vpmullw ymm4, ymm4, ymm0
					vpmullw ymm5, ymm5, ymm13
					weiter4:
					vmovdqu ymm12, ymm4
					lea r15, [rdx]
					sub r15, r14
					movzx r11, r15b
					shl r15, 16
					mov r15b, r11b
					movd xmm4, r15d
					pshufd  xmm4, xmm4, 0
					movdqu [rsp-16], xmm4
					vbroadcasti128 ymm4, [rsp-16]
					vmovdqu ymm6, ymm4
					vpmullw ymm4, ymm4, ymm12
					vpmullw ymm6, ymm6, ymm14
					weiter5:
					vpaddw ymm4, ymm4, ymm5
					vpaddw ymm6, ymm6, ymm7
					vpaddw ymm4, ymm4, ymm6
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
					vmovdqu [rsp-32], ymm4
					movzx rax, word ptr[rsp-32]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-30]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-28]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+r12+1]
					movzx rax, word ptr [rsp-26]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-24]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-22]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+r12+1]
					movzx rax, word ptr [rsp-20]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-18]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-16]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+r12+1]
					movzx rax, word ptr [rsp-14]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-12]
					xor rdx, rdx
					div r11
					mov [rcx+r15], al
					lea r15, [r15+1]
					movzx rax, word ptr [rsp-10]
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
					jl loop5
				lea r13, [r13+1]
				cmp r13, rdx
				jl loop4
			lea r10, [r10+1]
			cmp r10, r9
			jl loop3
			lea r12, [rax+rax*2]
			lea r11, [rdx-1]
			lea r14, [r11]
			imul r14, r12
			sub r15, r14
			lea r10, [rdx+rdx*4]
			lea r14, [r10+r10*2]
			sub r15, r14
			imul r9, r10, 3
			loop13:
				lea r14, [r10]
				loop14:
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
					jnz loop14
				sub r15, r9
				lea r15, [r15+r12]
				dec r11
				jnz loop13
				
		weiter:
		lea rbx, [rbx+5]
		cmp rbx, r8
		jl loop2
		imul r8, rdx
		lea r12, [r8+r8*2]
		lea r10, [rdx-1]
		loop12:
			lea r9, [rax]
			imul r13, r10, 3
			neg r13
			lea r13, [r12+r13-3]
			final_loop:
				mov rbx, [rcx+r13]
				lea r13, [r13+3]
				mov [rcx+r13], bl
				shr rbx, 8
				mov [rcx+r13+1], bl
				shr rbx, 8
				mov [rcx+r13+2], bl
				lea r13, [r13+r12-3]
				dec r9
				jnz final_loop
			dec r10
			jnz loop12
	end:
	ret
