// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract eSutartis {

    enum Status {
        Open,        // Task created, waiting for freelancer
        InProgress,  // Freelancer accepted task
        Completed,   // Freelancer marked task as completed
        Paid         // Client confirmed and paid
    }

    struct Task {
        address payable client;
        address payable freelancer;
        uint256 payment;
        Status status;
    }

    uint256 public taskCount;
    mapping(uint256 => Task) public tasks;

    event TaskCreated(
        uint256 indexed taskId,
        address indexed client,
        uint256 payment
    );

    event TaskAccepted(
        uint256 indexed taskId,
        address indexed freelancer
    );

    event TaskCompleted(
        uint256 indexed taskId
    );

    event TaskPaid(
        uint256 indexed taskId,
        address indexed freelancer,
        uint256 amount
    );

    // 1️. Client creates task and sends ETH
    function createTask() external payable {
        require(msg.value > 0, "Payment must be greater than 0");

        taskCount++;

        tasks[taskCount] = Task({
            client: payable(msg.sender),
            freelancer: payable(address(0)),
            payment: msg.value,
            status: Status.Open
        });

        emit TaskCreated(taskCount, msg.sender, msg.value);
    }

    // 2️. Freelancer accepts task
    function acceptTask(uint256 _taskId) external {
        Task storage task = tasks[_taskId];

        require(task.status == Status.Open, "Task is not open");
        require(msg.sender != task.client, "Client cannot accept own task");

        task.freelancer = payable(msg.sender);
        task.status = Status.InProgress;

        emit TaskAccepted(_taskId, msg.sender);
    }

    // 3️. Freelancer marks task as completed
    function markCompleted(uint256 _taskId) external {
        Task storage task = tasks[_taskId];

        require(task.status == Status.InProgress, "Task not in progress");
        require(msg.sender == task.freelancer, "Only freelancer can complete");

        task.status = Status.Completed;

        emit TaskCompleted(_taskId);
    }

    // 4️. Client confirms and releases payment
    function confirmAndPay(uint256 _taskId) external {
        Task storage task = tasks[_taskId];

        require(task.status == Status.Completed, "Task not completed");
        require(msg.sender == task.client, "Only client can confirm");

        task.status = Status.Paid;

        (bool success, ) = task.freelancer.call{value: task.payment}("");
        require(success, "Payment failed");

        emit TaskPaid(_taskId, task.freelancer, task.payment);
    }

    // 🔍 Helper function for frontend
    function getTask(uint256 _taskId)
        external
        view
        returns (
            address client,
            address freelancer,
            uint256 payment,
            Status status
        )
    {
        Task storage task = tasks[_taskId];
        return (
            task.client,
            task.freelancer,
            task.payment,
            task.status
        );
    }
}
