.PHONY: deps release clean test fmt xcompile
riftcrawl: deps
	go build riftcrawl.go

SOURCES=*.go
fmt: ${SOURCES}
	gofmt -w ${SOURCES}

test:
	go test -v

install: riftcrawl
	go install

clean:
	rm -rf pkg/*
	rm -f riftcrawl

deps:
	@(type -P gpm &>/dev/null && gpm) || (echo '[WARN] Install gpm (brew install gpm). Using gpm from the internets for this run.' && wget -qO- https://raw.github.com/pote/gpm/v1.1.1/bin/gpm | bash) ;\