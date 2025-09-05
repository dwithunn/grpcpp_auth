package main

import (
	"context"
	"fmt"
	"log"
	"time"

	"google.golang.org/grpc"

	pb "gateway/go/proto_pkgs/AuthService" // replace with your actual module path
)

func main() {
	// 1. Connect to the gRPC server
	conn, err := grpc.Dial("localhost:50051", grpc.WithInsecure())
	if err != nil {
		log.Fatalf("Failed to connect: %v", err)
	}
	defer conn.Close()

	// 2. Create client stub
	client := pb.NewServicesClient(conn)

	// 3. Build request message
	creds := &pb.Credentials{
		Id:       "alice",
		Password: "wonderland123",
	}

	// 4. Make RPC call with timeout
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	resp, err := client.Login(ctx, creds)
	if err != nil {
		log.Fatalf("Login RPC failed: %v", err)
	}

	// 5. Print the server’s response
	fmt.Printf("Received token: %s\n", resp.GetToken())
}
