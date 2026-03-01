/// Package Modules
import { Task } from '../../task';
import { Context } from '../../context';
import { Product } from '../../product';

/** Handles Executing Workflow Dispatches.. */
export class Integrate extends Task {
    //  PUBLIC METHODS  //

    /**
     * We skip integration if just mocking.
     * @param context               Release context.
     */
    override skip(context: Context.Readonly): boolean {
        return context.mock;
    }

    /**
     * Sets up the current integration sequence.
     * @param context               Release context.
     */
    override async setup(context: Context.Readonly) {
        context.spinner.start('Dispatching Workflow...');
    }

    /**
     * Handles ensuring varying conditions.
     * @param context               Release context.
     */
    override async execute(context: Context.Readonly) {
        await context.octo.actions.createWorkflowDispatch({
            repo: Product.repo,
            ref: context.branch,
            owner: Product.owner,
            workflow_id: 'release.yml',
            inputs: { tag: context.version.tag },
        });
    }

    /**
     * Tears down the current integration sequence.
     * @param context               Release context.
     */
    override async teardown(context: Context.Readonly) {
        context.spinner.succeed('Dispatched GitHub Workflow');
    }
}
